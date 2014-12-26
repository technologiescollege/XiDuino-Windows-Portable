//---------------------------------------------------------------------------

#ifndef XiDuinoH
#define XiDuinoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
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
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit1;
	TMenuItem *AllerplusloinBlocklyDuino1;
	TMenuItem *Wiki1;
	TMenuItem *Documentation1;
	TMenuItem *PrparerArduino1;
	TMenuItem *Utilisation1;
	TMenuItem *N3Mmentodescommandes1;
	TLabel *Label4;
	TLabel *Label5;
	TOpenDialog *Open_s2;
	TMenuItem *Ouvrir;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Aide1;
	TMenuItem *Apropos1;
	TMenuItem *Fichier;
	TMenuItem *N3;
	TMenuItem *ExemplesScratch21;
	TLabel *Label6;
	TMenuItem *Outils1;
	TMenuItem *N4;
	TMenuItem *Diaporamadeprsenation1;
	void __fastcall A_proposClick(TObject *Sender);
	void __fastcall AllerplusloinBlocklyDuino1Click(TObject *Sender);
	void __fastcall PrparerArduino1Click(TObject *Sender);
	void __fastcall Utilisation1Click(TObject *Sender);
	void __fastcall N3Mmentodescommandes1Click(TObject *Sender);
	void __fastcall Wiki1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Quitter1Click(TObject *Sender);
	void __fastcall OuvrirClick(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
	void __fastcall Apropos1Click(TObject *Sender);
	void __fastcall Diaporamadeprsenation1Click(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
