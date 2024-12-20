//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "Principal.h"
//---------------------------------------------------------------------------
class TFrame2 : public TFrame
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListBox *ListBox1;
	TListBox *ListBox2;
	void __fastcall ListBox1Click(TObject *Sender);
private:	// User declarations
	int type;
	vector<string> VDepartamentos;
	vector<string> VDisciplinas;
public:		// User declarations
	__fastcall TFrame2(TComponent* Owner);
	void setList(int type);
	Principal *Sistema;
    void listaTudo();
	void listaUniv();
	void listaDept();
	void listaDisc();
	void listaAlun();
	void listaUnivDept();
	void listaDeptDisc();
	void listaDiscAlun();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame2 *Frame2;
//---------------------------------------------------------------------------
#endif
