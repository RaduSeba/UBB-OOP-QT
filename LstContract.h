#pragma once
#include "Disciplina.h"
#include "Observer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

class ListaContract: public Observable {
private:
	vector<Disciplina> ContractDiscipline;
public:
	ListaContract();



	void addDisciplinatoLista(const Disciplina& d);


	void emptyList();


	void addRandomDisciplina(vector<Disciplina> original,const int& q);

	 vector<Disciplina>& getallContractDiscipline();

	void save_to_file(const string& filename);
};