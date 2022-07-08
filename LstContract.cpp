#include "LstContract.h"
#include <random>
#include <fstream>

ListaContract::ListaContract() {
	ContractDiscipline.clear();
}

void ListaContract::addDisciplinatoLista(const Disciplina& d) {
	ContractDiscipline.push_back(d);
	notify();
}

void ListaContract::emptyList() {
	ContractDiscipline.clear();
	notify();
}

void ListaContract::addRandomDisciplina(vector<Disciplina> original, const int& q)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, original.size() - 1);
	for (int i = 0; i < q; ++i) {
		int nr = dist(mt);
		addDisciplinatoLista(original[nr]);
	}
	notify();
}


void ListaContract::save_to_file(const string& filename) {

	ofstream fout(filename);
	fout << "First contract\n";
	fout << "Nrcrt. Denumire Ore Tip Cadru\n";
	int i = 0;
	for (auto& dis : ContractDiscipline) {
		fout << i++ << " " << dis.getDenumire() << " " << dis.getOre() << " " << dis.getTip() << " " << dis.getCadru() << "\n";
	}
}

vector <Disciplina>& ListaContract::getallContractDiscipline() {
	return ContractDiscipline;
}
