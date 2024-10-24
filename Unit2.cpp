//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <typeinfo>

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrame2 *Frame2;
//---------------------------------------------------------------------------
__fastcall TFrame2::TFrame2(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------

void TFrame2::setList(int type)
{
	VDepartamentos.clear();
    VDisciplinas.clear();
    this->type=type;
	ListBox2->Visible=true;
    this->ListBox2->Clear();
	this->ListBox1->Clear();
	switch (type) {
	case 0:
		this->Label1->Caption="Universidade";
		listaUniv();
		break;
	case 1:
		this->Label1->Caption="Departamento";
		listaDept();
		break;
	case 2:
		this->Label1->Caption="Disciplina";
		listaDisc();
		break;
	case 3:
		ListBox2->Visible=false;
		this->Label1->Caption="Aluno";
        listaAlun();
		break;
	case 4:
		ListBox2->Visible=false;
		this->Label1->Caption="Tudo";
		break;
	default:
		;
	}

}


void TFrame2::listaUniv(){
    this->Sistema->IteradorLUniversidades = Sistema->LUniversidades.LUniversidades.begin();

	while (Sistema->IteradorLUniversidades!= Sistema->LUniversidades.LUniversidades.end())
	{
		string aux;
		aux = (*(Sistema->IteradorLUniversidades))->getNome();
		AnsiString NomeUniv;
		NomeUniv = aux.data();

		ListBox1->Items->Add(NomeUniv);
		Sistema->IteradorLUniversidades++;
	}
}

void TFrame2::listaDept(){
	this->Sistema->IteradorLDepartamentos = Sistema->LDepartamentos.LDepartamentos.begin();

	while (Sistema->IteradorLDepartamentos!= Sistema->LDepartamentos.LDepartamentos.end())
	{
		string aux;
		VDepartamentos.push_back((*(Sistema->IteradorLDepartamentos))->getNome());
		aux = (*(Sistema->IteradorLDepartamentos))->getNome() + std::string(" da ") + (*(Sistema->IteradorLDepartamentos))->getUniversidade()->getNome();
		AnsiString NomeDept;
		NomeDept = aux.data();

		ListBox1->Items->Add(NomeDept);
		Sistema->IteradorLDepartamentos++;
	}
}

void TFrame2::listaDisc(){
	this->Sistema->IteradorLDisciplinas = Sistema->LDisciplinas.LDisciplinas.begin();

	while (Sistema->IteradorLDisciplinas!= Sistema->LDisciplinas.LDisciplinas.end())
	{
		string aux;
		VDisciplinas.push_back((*(Sistema->IteradorLDisciplinas))->getNome());
		aux = (*(Sistema->IteradorLDisciplinas))->getNome() + std::string(" do Departamento ") + (*(Sistema->IteradorLDisciplinas))->getDepartamento()->getNome();
		AnsiString NomeDisc;
		NomeDisc = aux.data();

		ListBox1->Items->Add(NomeDisc);
		Sistema->IteradorLDisciplinas++;
	}
}

void TFrame2::listaAlun(){
	this->Sistema->IteradorLAlunos = Sistema->LAlunos.LAlunos.begin();

	while (Sistema->IteradorLAlunos!= Sistema->LAlunos.LAlunos.end())
	{
		string aux;
		aux = (*(Sistema->IteradorLAlunos))->getNome();
		AnsiString NomeAluno;
		NomeAluno = aux.data();

		ListBox1->Items->Add(NomeAluno);
		Sistema->IteradorLAlunos++;
	}
}


void __fastcall TFrame2::ListBox1Click(TObject *Sender)
{
	this->ListBox2->Clear();
	switch (this->type) {
	case 0:
		listaUnivDept();
		break;
	case 1:
		listaDeptDisc();
		break;
	case 2:
		listaDiscAlun();
		break;
	default:
		break;
	}



}
//---------------------------------------------------------------------------


void TFrame2::listaUnivDept(){
	AnsiString NomeUniv;
	int pos = ListBox1->ItemIndex;
	NomeUniv = ListBox1->Items->operator [](pos);

	Universidade* pUniv = NULL;

	Sistema->IteradorLUniversidades = Sistema->LUniversidades.LUniversidades.begin();

	while (Sistema->IteradorLUniversidades!= Sistema->LUniversidades.LUniversidades.end())
	{
		string aux;
		aux = (*(Sistema->IteradorLUniversidades))->getNome();

		AnsiString NomeAux = aux.data();
		if ( NomeUniv == NomeAux )
		{
			pUniv = *(Sistema->IteradorLUniversidades);
			break;
		}

		Sistema->IteradorLUniversidades++;
	}

	if (pUniv)
	{
		int tam = (int)	pUniv->ObjLDepartamentos.size();
		for (int i = 0; i < tam; i++)
		{
			Departamento* pDepart = NULL;
			pDepart = pUniv->ObjLDepartamentos[i];
			const string aux = pDepart->getNome();

			AnsiString NomeAux = aux.data();
			ListBox2->Items->Add( NomeAux );
		}
	}
}

void TFrame2::listaDeptDisc(){
	string NomeDept;
	int pos = ListBox1->ItemIndex;
	NomeDept = VDepartamentos[pos];
	Departamento* pDept = NULL;

	Sistema->IteradorLDepartamentos = Sistema->LDepartamentos.LDepartamentos.begin();

	while (Sistema->IteradorLDepartamentos!= Sistema->LDepartamentos.LDepartamentos.end())
	{
		string aux;
		aux = (*(Sistema->IteradorLDepartamentos))->getNome();

		if ( NomeDept == aux )
		{
			pDept = *(Sistema->IteradorLDepartamentos);
			break;
		}

		Sistema->IteradorLDepartamentos++;
	}

	if (pDept)
	{
		int tam = (int)	pDept->pObjLDisciplinas.size();
		for (int i = 0; i < tam; i++)
		{
			Disciplina* pDisc = NULL;
			pDisc = pDept->pObjLDisciplinas[i];
			const string aux = pDisc->getNome();

			AnsiString NomeAux = aux.data();
			ListBox2->Items->Add( NomeAux );
		}
	}
}

void TFrame2::listaDiscAlun(){
	string NomeDisc;
	int pos = ListBox1->ItemIndex;
	NomeDisc = VDisciplinas[pos];

	Disciplina* pDisc = NULL;

	Sistema->IteradorLDisciplinas = Sistema->LDisciplinas.LDisciplinas.begin();

	while (Sistema->IteradorLDisciplinas!= Sistema->LDisciplinas.LDisciplinas.end())
	{
		string aux;
		aux = (*(Sistema->IteradorLDisciplinas))->getNome();

		if ( NomeDisc == aux )
		{
			pDisc = *(Sistema->IteradorLDisciplinas);
			break;
		}

		Sistema->IteradorLDisciplinas++;
	}

	if (pDisc)
	{
		int tam = (int)	pDisc->ObjLAlunos.size();
		for (int i = 0; i < tam; i++)
		{
			Aluno* pAlun = NULL;
			pAlun = pDisc->ObjLAlunos[i];
			const string aux = pAlun->getNome();

			AnsiString NomeAux = aux.data();
			ListBox2->Items->Add( NomeAux );
		}
	}
}
