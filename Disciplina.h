#pragma once
#include <vector>
#include <string>
#include "Departamento.h"
#include "Aluno.h"

using namespace std;

class Disciplina
{
private:
	int id;
	string nome;
	Departamento* pDeptoAssociado;
public:
	Disciplina(int id);
	~Disciplina();
	void setId(int i);
	int getId();
	void setNome(const char* n);
	string getNome();
	void setDepartamento(Departamento* pd);
	Departamento* getDepartamento();
	void incluaAluno(Aluno* pa);
	vector<Aluno*> ObjLAlunos;
};