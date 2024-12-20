#include "Departamento.h"
#include "Universidade.h"
#include "Disciplina.h"

// construtora e destrutora
Departamento::Departamento(int id)
{
	this->id = id;
}
Departamento::~Departamento()
{
}
// sets e gets
void Departamento::setNome(const char* n)
{
	nome=n;
}
string Departamento::getNome()
{
	return nome;
}
void Departamento::setUniversidade(Universidade* pu)
{
	pUniv = pu;
}
Universidade* Departamento::getUniversidade()
{
	return pUniv;
}
int Departamento::getId() {
	return id;
}

// metodos de inclusao na lista e de listagem
void Departamento::incluaDisciplina(Disciplina* pdi)
{
	pObjLDisciplinas.push_back(pdi);
	pdi->setDepartamento(this);
}
