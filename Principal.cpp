// Data: 15/05/2017 - 1o Semestre de 2018
// Prof. Dr. Jean M. Simao - DAINF/UTFPR Curitiba-Central
// Autor: Monitor Vitor C. M. Correa

// UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA - Campus de Curitiba Central
// Departamento Academico de Informatica (DAINF)
// Disciplina: Tecnicas de Programacao - CSE20
// Sistema Academico - Slides 1 ao 8
// Exemplo de referencia para os exercicios e atividades propostos em sala

// Curso: Engenharia da Computacao / Sistemas de Informacao
// Turma: S71 / S02.

#include "Principal.h"

#include <fstream>

using std::cout;
using std::endl;
using std::cin;


Principal::Principal() :
	// contadores da quantidade de objetos existentes
	cont_idUniv(0),
	cont_idAluno(0),
	cont_idDisc(0),
	cont_idDepart(0)
{

}
Principal::~Principal() {

}

// funcoes para cadastro de novos objetos
void Principal::CadUniversidade(const char* univ)
{
	Universidade* puniv = new Universidade(cont_idUniv++);
	puniv->setNome(univ);
	LUniversidades.incluaUniversidade(puniv);
}

void Principal::CadDepartamento(const char* univ, const char* depart)
{
	Universidade* puniv = LUniversidades.localizar(univ);
	if (puniv != NULL)
	{
		Departamento* pdepart = new Departamento(cont_idDepart++);
		pdepart->setNome(depart);
		puniv->incluaDepartamento(pdepart);
		LDepartamentos.incluaDepartamento(pdepart);
	}
}

void Principal::CadDisciplina(const char* depart, const char* disci) {
	Departamento* pdepart = LDepartamentos.localizar(depart);
	if (pdepart != NULL)
	{
		Disciplina* pdisc = new Disciplina(cont_idDisc++);
		pdisc->setNome(disci);
		pdepart->incluaDisciplina(pdisc);
		LDisciplinas.incluaDisciplina(pdisc);
	}
}

void Principal::CadAluno(const char* disci, const char* aluno, int ra)
{
	Aluno* pal;
	Disciplina* pdisc = LDisciplinas.localizar(disci);
	if (pdisc != NULL)
	{
		pal = new Aluno(cont_idAluno++);
		pal->setNome(aluno);
		pal->setRA(ra);
		pdisc->incluaAluno(pal);
		LAlunos.incluaAluno(pal);
	}
}
// funcoes para a gravacao de objetos em arquivo
void Principal::GravarTudo() {
	GravarUniversidades();
	GravarDepartamentos();
	GravarDisciplinas();
	GravarAlunos();
}
void Principal::GravarUniversidades() {
	std::ofstream out("universidades.dat", std::ios::out);
	if (out) {
		IteradorLUniversidades = LUniversidades.LUniversidades.begin();

		while (IteradorLUniversidades!= LUniversidades.LUniversidades.end())
		{
			std::string str(((*(IteradorLUniversidades))->getNome() + std::string(" ")));
			out << str << (*(IteradorLUniversidades))->getId() << endl;
			IteradorLUniversidades++;
		}
			
	}
	out.close();
}
void Principal::GravarDepartamentos() {
	std::ofstream out("departamentos.dat", std::ios::out);
	if (out) {
		IteradorLDepartamentos = LDepartamentos.LDepartamentos.begin();
		while (IteradorLDepartamentos!= LDepartamentos.LDepartamentos.end()) {
			Departamento* aux = (*(IteradorLDepartamentos));
			std::string str(aux->getNome() + std::string(" ") + std::to_string(aux->getId()) + std::string(" ") + aux->getUniversidade()->getNome());
			out << str << endl;
			IteradorLDepartamentos++;
		}
	}
	out.close();
}
void Principal::GravarDisciplinas() {
	std::ofstream out("disciplinas.dat", std::ios::out);
	if (out) {
		IteradorLDisciplinas = LDisciplinas.LDisciplinas.begin();
		while (IteradorLDisciplinas!= LDisciplinas.LDisciplinas.end()) {
			Disciplina* aux = (*(IteradorLDisciplinas));
			std::string str(aux->getNome() + std::string(" ") + std::to_string(aux->getId()) + std::string(" ") + aux->getDepartamento()->getNome());
			out << str << endl;
			IteradorLDisciplinas++;
		}
	}
	out.close();
}
void Principal::GravarAlunos() {
	std::ofstream out("alunos.dat", std::ios::out);
	if (out) {
		IteradorLAlunos = LAlunos.LAlunos.begin();
		while (IteradorLAlunos!= LAlunos.LAlunos.end()) {
			Aluno* aux = (*(IteradorLAlunos));
			std::string str(aux->getNome() + std::string(" ") + std::to_string(aux->getRA()) + std::string(" ") + std::to_string(aux->getId()) + std::string(" ") + aux->getDisciplina()->getNome());
			out << str << endl;
			IteradorLAlunos++;
		}
	}
	out.close();
}
// auncoes para a recuperacao de objetos em arquivo
void Principal::RecuperarTudo() {
	RecuperarUniversidades();
	RecuperarDepartamentos();
	RecuperarDisciplinas();
	RecuperarAlunos();
}
void Principal::RecuperarUniversidades() {
	std::ifstream in("universidades.dat", std::ios::in);
	if (in) {
		char nome[150];
		int id;
		while (in >> nome >> id) {
			Universidade* puniv = new Universidade(id);
			puniv->setNome(nome);
			LUniversidades.incluaUniversidade(puniv);
			cont_idUniv++;
		}
	}
	in.close();
}
void Principal::RecuperarDepartamentos() {
	std::ifstream in("departamentos.dat", std::ios::in);
	if (in) {
		char nome[150], nomeuniv[150];
		int id;
		while (in >> nome >> id >> nomeuniv) {
			Universidade* puniv = LUniversidades.localizar(nomeuniv);
			if (puniv) {
				Departamento* pdep = new Departamento(id);
				pdep->setNome(nome);
				puniv->incluaDepartamento(pdep);
				LDepartamentos.incluaDepartamento(pdep);
				cont_idDepart++;
			}
		}
	}
	in.close();
}
void Principal::RecuperarDisciplinas() {
	std::ifstream in("disciplinas.dat", std::ios::in);
	if (in) {
		char nome[150], nomedep[150];
		int id;
		while (in >> nome >> id >> nomedep) {
			Departamento* pdep = LDepartamentos.localizar(nomedep);
			if (pdep) {
				Disciplina* pdisc = new Disciplina(id);
				pdisc->setNome(nome);
				pdep->incluaDisciplina(pdisc);
				LDisciplinas.incluaDisciplina(pdisc);
				cont_idDisc++;
			}
		}
	}
	in.close();
}
void Principal::RecuperarAlunos() {
	std::ifstream in("alunos.dat", std::ios::in);
	if (in) {
		char nome[150], nomedisc[150];
		int id, RA;
		while (in >> nome >> RA >> id >> nomedisc) {
			Disciplina* pdisc = LDisciplinas.localizar(nomedisc);
			if (pdisc) {
				Aluno* pal = new Aluno(id);
				pal->setNome(nome);
				pal->setRA(RA);
				pdisc->incluaAluno(pal);
				LAlunos.incluaAluno(pal);
				cont_idAluno++;
			}
		}
	}
	in.close();
}