//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream> //pour l'ouverture des fichiers
#include <winsock2.h> //pour l'adresse IP
#pragma comment(lib, "Ws2_32.lib") //pour l'adresse IP

#include <windows.h>
#include <tinyxml.h>
#include <stdlib.h>
using namespace std;

#include <IniFiles.hpp> //pour le fichier INI
#pragma hdrstop

#include "Xi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterfaceXi *InterfaceXi;

TIniFile *INI = new TIniFile(ExtractFilePath(Application->ExeName)+ "xi.ini");
//listes pour récupérer le contenu du fichier INI
int xi_port=666;
int xi_com=69;
int choix_langue;
AnsiString locate_scratch2="Scratch 2.exe";
AnsiString locate_librairie;
AnsiString locate_project;
AnsiString locate_doc;
//listes pour les menus dynamiques
TStringList *Examples = new TStringList;
TStringList *Biblio = new TStringList;
TStringList *Aides = new TStringList;
TStringList *Docs = new TStringList;
TStringList *Extensions1 = new TStringList;
TStringList *Extensions2 = new TStringList;

bool cachIP=false;

//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::InitINI()
{
  //écriture dans le fichier INI des variables utiles
  INI->WriteInteger("port COM", "xi_com", 3);      //port par défaut pour initialiser
  INI->WriteInteger("port serveur", "xi_port", 1234);      //port par défaut pour initialiser
  INI->WriteInteger("langue", "langue", 0); //dans le fichier label.xml, à la balise <Langues>, cela correspond au n° du rang de la langue
  INI->WriteString("locate Scratch2", "locate_scratch2", "Scratch 2.exe"); //chemin par défaut pour initialiser
  //dossiers à utiliser pour les documents
  INI->WriteString("locate Librairie", "locate_librairie", ExtractFilePath(Application->ExeName) + "bibliotheque\\"); //chemin par défaut pour initialiser
  INI->WriteString("locate Project", "locate_project", ExtractFilePath(Application->ExeName) + "projets\\"); //chemin par défaut pour initialiser
  INI->WriteString("locate Documentation", "locate_doc", ExtractFilePath(Application->ExeName) + "documentation\\"); //chemin par défaut pour initialiser
}
//---------------------------------------------------------------------------
__fastcall TInterfaceXi::TInterfaceXi(TComponent* Owner)
	: TForm(Owner)
{
  //vérification de l'existence du fichier INI, sinon le recréé
  if (!FileExists(ExtractFilePath(Application->ExeName)+ "xi.ini"))
	 InitINI();
  //lecture du fichier INI
  xi_port=INI->ReadInteger("port serveur","xi_port",1234);
  xi_com=INI->ReadInteger("port COM","xi_com",4);
  choix_langue=INI->ReadInteger("langue", "langue", 0);
  locate_scratch2=INI->ReadString("locate Scratch2", "locate_scratch2", "Scratch 2.exe");
  locate_librairie=INI->ReadString("locate Librairie", "locate_librairie", ExtractFilePath(Application->ExeName) + "bibliotheque\\");
  locate_project=INI->ReadString("locate Project", "locate_project", ExtractFilePath(Application->ExeName) + "projets\\");
  locate_doc=INI->ReadString("locate Documentation", "locate_doc", ExtractFilePath(Application->ExeName) + "documentation\\");

  //nettoie les champs TEdit et y place la valeur lue dans le INI
  Edit1->Clear();
  Edit2->Clear();
  Edit1->Text=IntToStr(xi_com);
  Edit2->Text=IntToStr(xi_port);
  Extensions1->Add(".sb2");
  // Appel à Search, avec pour liste des fichiers, les items des listes Bibilo & Examples.
  SearchEx(locate_librairie, Extensions1, Biblio,0);
  SearchEx(locate_project, Extensions1, Examples,1);
  delete Extensions1;
  Extensions2->Add(".pdf");
  Extensions2->Add(".odt");
  Extensions2->Add(".lnk");
  Extensions2->Add(".url");
  Extensions2->Add(".html");
  Extensions2->Add(".htm");  
  // Appel à SearchDocs, avec pour liste des fichiers les items de Documentation.
  SearchDocs(locate_doc, Extensions2, Docs,2);
  delete Extensions2;

  //appel à la procédure pour gérer les langues
  AnsiString file = ExtractFilePath(Application->ExeName) + "label.xml";
  langue = new GestionLangue;
  langue->Init(InterfaceXi->Langues,file.c_str(),(ptrOnClick)&LanguesClick);
  //après l'initialisation des langues, le système pioche la langue précédemment sélectionnée
  langue->Change(choix_langue);

	InterfaceXi->AutoSize=true;
	ListBox1->Visible=false;
	Label7->Visible=false;
	Label9->Visible=true;
	Label10->Visible=true;
	Label11->Visible=false;

}


//-------------------------recherche des fichiers sb2 pour les lister dans le menu Fichier--------------------------------------------------
void __fastcall TInterfaceXi::SearchEx(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu)
{
  TSearchRec Infos_fichier;
  TMenuItem *NewItem = new TMenuItem(this);
  if (!FindFirst(FilePath+"*.*", faAnyFile, Infos_fichier))
  do
  {
	for (int i = 0 ; i < Extensions->Count ; i++)
	{
	  if (ExtractFileExt(Infos_fichier.Name).LowerCase() == Extensions->Strings[i].LowerCase())
	  {
		//ajout dans la liste d'une ligne avec le chemin+nom du fichier trouvé
		ListeFichiers->Add(ExpandFileName(Infos_fichier.Name));
		//nettoie le nom de fichier de son extension sb2 pour le nom seul du fichier, sans le chemin
		AnsiString CleanName = StringReplace(Infos_fichier.Name, ".sb2", "",TReplaceFlags() << rfReplaceAll);
		//rajout d'entrées dans le menu
		NewItem = new TMenuItem(this);
		NewItem->Caption = CleanName;
		NewItem->Name = CleanName;
		//stockage du chemin complet + nom de fichier pour la fonction ExempleClick
		NewItem->Hint = FilePath + Infos_fichier.Name.c_str();
		NewItem->OnClick=ExempleClick;
		//rajout au bon endroit de l'entrée dans le menu
		MainMenu1->Items->Items[0]->Items[RangMenu]->Add(NewItem);
	  }
	}
  }
  while(!FindNext(Infos_fichier));
  FindClose(Infos_fichier);
}
//---------------------associer chaque entrée dynamique dans Biblio & Exemples à leur lancement-------------------
void __fastcall TInterfaceXi::ExempleClick(TObject *Sender)
{
AnsiString CheminNomFichier;
ofstream fichier_s2("scratch2.bat", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		if(fichier_s2)
		{
			   //récupération des infos de l'entrée TMenu qui a déclenché cette fonction
			   CheminNomFichier=static_cast<TMenuItem*>(Sender)->Hint;
			   fichier_s2 << "@echo off\nbreak ON\nrem fichiers BAT et fork créés par Sébastien CANET\ncls\nSET currentpath=%~dp1\nSET dossier_scratch="<< '"' << locate_scratch2.c_str() << '"'<< "\nstart %dossier_scratch% " << '"' << CheminNomFichier.c_str() << '"';
			   fichier_s2.close();
		}
		else ShowMessage(Popup->Items->Strings[0]);
ShellExecute(0, 0, "scratch2.bat", 0, 0 , SW_HIDE );
}
//-------------------------recherche des fichiers de docs pour les lister dans les menus Aide & Documentation---------------
void __fastcall TInterfaceXi::SearchDocs(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu)
{
  TSearchRec Infos_fichier;
  TMenuItem *NewItem = new TMenuItem(this);
  if (!FindFirst(FilePath+"*.*", faAnyFile, Infos_fichier))
  do
  {
	for (int i = 0 ; i < Extensions->Count ; i++)
	{
	  if (ExtractFileExt(Infos_fichier.Name).LowerCase() == Extensions->Strings[i].LowerCase())
	  {
		//ajout dans la liste d'une ligne avec le chemin+nom du fichier trouvé
		ListeFichiers->Add(ExpandFileName(Infos_fichier.Name));
		//nettoie le nom de fichier de son extension pour le nom seul du fichier, sans le chemin
		AnsiString CleanName = StringReplace(Infos_fichier.Name, Extensions->Strings[i].LowerCase(), "",TReplaceFlags() << rfReplaceAll);
		//rajout d'entrées dans le menu
		NewItem = new TMenuItem(this);
		NewItem->Caption = Infos_fichier.Name;
		NewItem->Name = CleanName;
		//stockage du chemin complet + nom de fichier pour la fonction ExempleClick
		NewItem->Hint = FilePath + Infos_fichier.Name.c_str();
		NewItem->OnClick=DocsClick;
		//rajout au bon endroit de l'entrée dans le menu
		MainMenu1->Items->Items[RangMenu]->Add(NewItem);
	  }
	}
  }
  while(!FindNext(Infos_fichier));
  FindClose(Infos_fichier);
}
//---------------------associer chaque entrée dynamique dans Biblio & Exemples à leur lancement-------------------
void __fastcall TInterfaceXi::DocsClick(TObject *Sender)
{
//récupération des infos de l'entrée TMenu qui a déclenché cette fonction
AnsiString CheminNomFichier=static_cast<TMenuItem*>(Sender)->Hint;

ShellExecute(0, 0, CheminNomFichier.c_str(), 0, 0 , SW_HIDE );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::A_proposClick(TObject *Sender)
{
ShellExecute(0, 0, "https://github.com/technologiescollege/XiDuino-Windows-Portable", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::SiteofficieldeXiClick(TObject *Sender)
{
ShellExecute(0, 0, "http://mryslab.blogspot.fr/", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::AllerplusloinBlocklyDuino1Click(TObject *Sender)
{
ShellExecute(0, 0, "http://www.technologiescollege.fr/blockly@rduino/", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Diaporamadeprsenation1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\0-presentation\\Xi.odp", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::PrparerArduino1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\1.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Utilisation1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\2.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::N4Principesdeprogrammation1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\3.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::N3Mmentodescommandes1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\4.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Wiki1Click(TObject *Sender)
{
ShellExecute(0, 0, "http://tic.technologiescollege.fr/wiki", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Button3Click(TObject *Sender)
{
ShellExecute(0, 0, "http://scratch.mit.edu/projects/editor/", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Button2Click(TObject *Sender)
{
ofstream fichier_s2("scratch2.bat", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		if(fichier_s2)
		{
				fichier_s2 << "@echo off\nbreak ON\nrem fichiers BAT et fork créés par Sébastien CANET\ncls\nSET currentpath=%~dp1\nSET dossier_scratch="<< '"' << locate_scratch2.c_str() << '"'<< "\nstart %dossier_scratch% %currentpath%bibliotheque\\fichier_depart_Xi.sb2";
				fichier_s2.close();
		}
		else ShowMessage(Popup->Items->Strings[1]);
ShellExecute(0, 0, "scratch2.bat", 0, 0 , SW_HIDE );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Button1Click(TObject *Sender)
{
xi_com=this->Edit1->Text.ToInt();
xi_port=this->Edit2->Text.ToInt();
INI->WriteInteger("port COM", "xi_com", xi_com);
INI->WriteInteger("port serveur", "xi_port", xi_port);
ofstream fichier_s2a("xi_portable_Win.bat", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		if(fichier_s2a)
		{
				fichier_s2a << "@echo off\nbreak ON\nrem fichiers BAT et fork créés par Sébastien CANET\ncls\nSET currentpath=%~dp1\ncd %currentpath%\nstart .\\nodejs\\node.exe xiserver.js ard null 0 COM" << xi_com << " " << xi_port;
				fichier_s2a.close();
		}
		else ShowMessage(Popup->Items->Strings[2]);
ShellExecute(0, 0, "xi_portable_Win.bat", 0, 0 , SW_HIDE );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Quitter1Click(TObject *Sender)
{
InterfaceXi->Close();
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::OuvrirClick(TObject *Sender)
{
if (Open_s2->Execute()==true) locate_scratch2=Open_s2->FileName.c_str();
//écriture dans le fichier INI
//DeleteKey("locate Scratch2", "locate_scratch2");
INI->WriteString("locate Scratch2", "locate_scratch2", locate_scratch2);
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceXi::Edit1KeyPress(TObject *Sender, char &Key)
{
  if (Key < '0' || Key >'9')
	{
	ShowMessage(Popup->Items->Strings[3]);
	Key=NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::Edit2KeyPress(TObject *Sender, char &Key)
{
//vérifie si chaque touche pressée est bien un chiffre
if (Key < '0' || Key >'9')
	{
	ShowMessage(Popup->Items->Strings[4]);
	Key=NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::Apropos1Click(TObject *Sender)
{
ShowMessage(Popup->Items->Strings[5]);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::nodejsClick(TObject *Sender)
{
ShellExecute(0, 0, "install_nodejs_portable.bat", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::AfficherladresseIPduposte1Click(TObject *Sender)
{
// agrandit la fenêtre pour montrer la ListBox et y afficher les adresses IP du poste
ListBox1->Clear();
if (cachIP==true)
	{
	//InterfaceXi->ClientWidth=510;
	//InterfaceXi->Constraints->MinWidth=510;
	//InterfaceXi->Constraints->MaxWidth=510;
	cachIP=false;
	ListBox1->Visible=false;
	Label7->Visible=false;
	Label11->Visible=false;
	AfficherladresseIPduposte1->Caption = Popup->Items->Strings[6];
	}
	else {
			//InterfaceXi->ClientWidth=670;
			//InterfaceXi->Constraints->MinWidth=670;
			//InterfaceXi->Constraints->MaxWidth=670;
			AfficherladresseIPduposte1->Caption = Popup->Items->Strings[7];
			cachIP=true;
			ListBox1->Visible=true;
			Label7->Visible=true;
			Label11->Visible=true;
			}

WORD wVersionRequested;
WSADATA wsaData;
char name[255];
PHOSTENT hostinfo;
wVersionRequested = MAKEWORD( 1, 1 );
char *ip;
if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
if( gethostname ( name, sizeof(name)) == 0)
	{
	if((hostinfo = gethostbyname(name)) != NULL)
		{
		int nCount = 0;
		while(hostinfo->h_addr_list[nCount])
			{
			ListBox1->Items->Add( inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[nCount]));
			nCount++;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::InitClick(TObject *Sender)
{
DeleteFile("xi.ini");
InitINI();
//nettoie les champs des TEdit et y place la valeur lue dans le INI
Edit1->Clear();
Edit2->Clear();
//procédure de contrôle si le fichier INI est mal rempli
xi_com=INI->ReadInteger("port COM", "xi_com", 3);
xi_port=INI->ReadInteger("port serveur", "xi_port", 1234);
Edit1->Text=IntToStr(xi_com);
Edit2->Text=IntToStr(xi_port);

}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::LanguesClick(TObject *Sender)
{
INI->WriteInteger("langue", "langue", ((TMenuItem*)Sender)->Tag);
langue->Change(((TMenuItem*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::Gestionnairedepriphriques1Click(TObject *Sender)
{
ShellExecute(0, 0, "devmgmt.msc", 0, 0 , SW_HIDE );	
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::SiteofficielArduino1Click(TObject *Sender)
{
ShellExecute(0, 0, "http://arduino.cc/en/Main/Software", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::lchargerlesdrivers1Click(TObject *Sender)
{
ShellExecute(0, 0, "https://github.com/technologiescollege/drivers", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::Localiserledossierbibliothque1Click(
      TObject *Sender)
{
if (OpenDialog->Execute()==true) locate_librairie=ExtractFilePath(OpenDialog->FileName);
//écriture dans le fichier INI
INI->WriteString("locate Librairie", "locate_librairie", locate_librairie);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::Localiserledossierprojets1Click(TObject *Sender)
{
if (OpenDialog->Execute()==true) locate_project=ExtractFilePath(OpenDialog->FileName);
//écriture dans le fichier INI
INI->WriteString("locate Project", "locate_project", locate_project);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceXi::Localiserledossierdocumentation1Click(
      TObject *Sender)
{
if (OpenDialog->Execute()==true) locate_doc=ExtractFilePath(OpenDialog->FileName);
//écriture dans le fichier INI
INI->WriteString("locate Documentation", "locate_doc", locate_doc);
}
//---------------------------------------------------------------------------

