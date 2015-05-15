//---------------------------------------------------------------------------

#ifndef XiH
#define XiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>

#include <FileCtrl.hpp>
#include <IniFiles.hpp>
#include <string>
#include "GestionLangue.h"
//---------------------------------------------------------------------------
class TInterfaceXi : public TForm
{
__published:	// Composants gérés par l'EDI
	TMainMenu *MainMenu1;
	TMenuItem *Quitter1;
	TMenuItem *A_propos;
	TImage *Image1;
	TImage *Image2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label2;
	TEdit *Edit1;
	TMenuItem *BlocklyArduino;
	TMenuItem *Wiki1;
	TMenuItem *Documentation1;
	TMenuItem *PrparerArduino1;
	TMenuItem *Utilisation1;
	TMenuItem *N3Mmentodescommandes1;
	TLabel *Label4;
	TLabel *Label5;
	TMenuItem *Ouvrir;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Aide1;
	TMenuItem *Apropos1;
	TMenuItem *Fichier;
	TMenuItem *N3;
	TMenuItem *ExemplesScratch2;
	TLabel *Label6;
	TMenuItem *Outils1;
	TMenuItem *N4;
	TMenuItem *Diaporamadeprsenation1;
	TMenuItem *nodejs;
	TEdit *Edit2;
	TMenuItem *AfficherladresseIPduposte1;
	TMenuItem *N5;
	TOpenDialog *Open_s2;
	TListBox *ListBox1;
	TLabel *Label7;
	TMenuItem *SiteofficieldeXi;
	TMenuItem *Langues;
	TMenuItem *Bibliothque;
	TMenuItem *Gestionnairedepriphriques1;
	TMenuItem *N6;
	TMenuItem *Init;
	TMenuItem *N4Principesdeprogrammation1;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TMenuItem *N7;
	TMenuItem *Localiserledossierbibliothque1;
	TMenuItem *Localiserledossierprojets1;
	TMenuItem *Localiserledossierdocumentation1;
	TMenuItem *SiteofficielArduino1;
	TMenuItem *lchargerlesdrivers1;
	TOpenDialog *OpenDialog;
	TComboBox *Popup;
	TMenuItem *InstallDrivers;
	TMenuItem *w32;
	TMenuItem *w64;
	TMenuItem *Upload;
	TMenuItem *Firmata_Uno;
	TMenuItem *Firmata_Mega;
	TMenuItem *Locate;
	TMenuItem *Drivers;
	TMenuItem *Links;
	TMenuItem *N8;
	TMenuItem *N9;
	void __fastcall A_proposClick(TObject *Sender);
	void __fastcall BlocklyArduinoClick(TObject *Sender);
	void __fastcall PrparerArduino1Click(TObject *Sender);
	void __fastcall Utilisation1Click(TObject *Sender);
	void __fastcall N3Mmentodescommandes1Click(TObject *Sender);
	void __fastcall Wiki1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Quitter1Click(TObject *Sender);
	void __fastcall OuvrirClick(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
	void __fastcall Apropos1Click(TObject *Sender);
	void __fastcall Diaporamadeprsenation1Click(TObject *Sender);
	void __fastcall nodejsClick(TObject *Sender);
	void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
	void __fastcall AfficherladresseIPduposte1Click(TObject *Sender);
	void __fastcall SiteofficieldeXiClick(TObject *Sender);
	void __fastcall InitINI();
	void __fastcall SearchEx(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu);
	void __fastcall ExempleClick(TObject *Sender);
	void __fastcall SearchDocs(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu);
	void __fastcall DocsClick(TObject *Sender);
	void __fastcall InitClick(TObject *Sender);
	void __fastcall Gestionnairedepriphriques1Click(TObject *Sender);
	void __fastcall N4Principesdeprogrammation1Click(TObject *Sender);
	void __fastcall SiteofficielArduino1Click(TObject *Sender);
	void __fastcall lchargerlesdrivers1Click(TObject *Sender);
	void __fastcall Localiserledossierbibliothque1Click(TObject *Sender);
	void __fastcall Localiserledossierprojets1Click(TObject *Sender);
	void __fastcall Localiserledossierdocumentation1Click(TObject *Sender);
	void __fastcall Firmata_UnoClick(TObject *Sender);
	void __fastcall Firmata_MegaClick(TObject *Sender);
	void __fastcall w32Click(TObject *Sender);
	void __fastcall w64Click(TObject *Sender);
	void __fastcall DriversClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
	TLabel * interLabel ;
	TButton * interButton ;
	TInterfaceXi * interInterfaceXi ;
	TGroupBox * interGroupeBox ;
	TComboBox * interComboBox ;
	TCheckBox * interCheckBox ;
	TRadioGroup * interRadioGroupe ;
	TMenuItem * interMenuItem ;
	GestionLangue * langue;
public:		// Déclarations de l'utilisateur
	void __fastcall LanguesClick(TObject *Sender);
	__fastcall TInterfaceXi(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterfaceXi *InterfaceXi;
//---------------------------------------------------------------------------
#endif
