#include "ContractRepo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

using std::ostream;
using std::stringstream;




bool ContractRepo::exportFisier(const string filename, const string type)
{
	string nume_fisier = filename + '.' + type;
	std::ofstream fout(nume_fisier);
	if (type == "html" || type == "csv")
	{
		for (const Disciplina& d : this->allDiscipline)
		{
			fout << "Denumire: " << d.getDenumire() << " Numar de ore: " << d.getOre() << " Tip: " << d.getTip() << " Cadru didactic: " << d.getCadru() << endl;
		}
		return true;
	}
	return false;
}







void ContractRepo::store(const Disciplina& d)
{
	this->allDiscipline.push_back(d);
}





void ContractRepo::delet(int poz)
{
	this->allDiscipline.erase(allDiscipline.begin() + poz);
}



void ContractRepo::modifica(const Disciplina& d, int poz) {
	this->allDiscipline[poz] = d;
}



vector<Disciplina>& ContractRepo::getAllDiscipline() {
	return allDiscipline;
}

ostream& operator<<(ostream& out, const ContractRepoException& ex) {
	for (const auto& mesg : ex.msg) {
		out << mesg << "\n";
	}
	return out;
}

FileRepo::FileRepo(string fn) {
	filename = move(fn);
	load_from_file();
}


void FileRepo::load_from_file() {
	ifstream fin(filename);
	string str;
	while (getline(fin, str)) {
		 stringstream ss(str);

		 string word;
		 vector<string> dis;
		 while (getline(ss, word, ';')) {
			 dis.push_back(word);
		 }
		 int nr = 0;
		 for (auto& ch : dis[1]) {
			 nr = nr * 10 + (ch - '0');
		 }
		 while (getline(ss, word, ';')) {
			 dis.push_back(word);
		 }
		 ContractRepo::store(Disciplina(dis[0], nr, dis[2], dis[3]));
	}
	fin.close();
}

void FileRepo::save_to_file() {
	ofstream fout(filename);
	int index = 0;
	for (auto& it : ContractRepo::getAllDiscipline()) {
		fout << it.getDenumire() << ";" << it.getOre() << ";" << it.getTip() << ";" << it.getCadru();
		++index;
		if (index != ContractRepo::getAllDiscipline().size())
		{
			fout << "\n";
		}
	}
	fout.close();
}


void RepoProb::store(const Disciplina& d) {
	det_luck();
	allDiscipline.insert(make_pair(allDiscipline.size(), d));
}


void RepoProb::delet(int poz) {

	det_luck();
	allDiscipline.erase(poz);
	map<int, Disciplina>sec;
	sec.clear();
	for (auto& it : allDiscipline) {
		sec.insert(make_pair(sec.size(), it.second));
	}
	allDiscipline = sec;
}


void RepoProb::modifica(const Disciplina& d, int poz) {
	det_luck();
	for (auto& it : allDiscipline) {
		if (it.first == poz)
		{
			allDiscipline.erase(poz);
			allDiscipline.insert(make_pair(poz, d));
			break;
		}
	}
}



vector<Disciplina>& RepoProb::getAllDiscipline() {


	all.clear();
	for (auto& it : allDiscipline) {
		all.push_back(it.second);
	}
	return all;
}


RepoProb::RepoProb(float chance) {
	prob = chance;
	allDiscipline.clear();
}


void RepoProb::det_luck() {


	auto prb = int(prob * 10);
	int nr = rand() % 10 + 1;
	if (nr <= prb) {
		return;
	}
	throw BadLuckException("Teapa frt\n");
}






void testAddRepo() {
	ContractRepo testRepo;


	Disciplina d1{ "Matematica",10,"gras","ubb" };
	testRepo.store(d1);
	assert(testRepo.getAllDiscipline().size() == 1);

	Disciplina  d2{ "informatica",211,"real","Oviedo" };
	Disciplina d3{ "Matematica", 3,"ss","ubb" };
	try {
		testRepo.store(d3);
	}
	catch (ContractRepoException) {
		assert(true);
	}
	testRepo.exportFisier("seb", "html");


}
void testAddrepo2() {
	auto prp = RepoProb(1);
	Disciplina d1{ "Matematica",10,"gras","ubb" };
	Disciplina d2{ "so",3,"test","fork" };
	prp.store(d1);
	prp.store(d2);
	prp.delet(0);
	prp.modifica(d2, 0);
	assert(prp.getAllDiscipline().size() == 1);

	//assert(testRepo.getAllDiscipline().size() == 1);



}
void testAddrepo3() {
	FileRepo frp{ "test.txt" };
	Disciplina d1{ "Matematica",10,"gras","ubb" };
	Disciplina d2{ "so",3,"test","fork" };
	frp.store(d1);
	frp.store(d2);
	frp.delet(0);
	frp.modifica(d2, 0);
	assert(frp.getAllDiscipline().size() == 1);
	frp.delet(0);
	//assert(testRepo.getAllDiscipline().size() == 1);



}

void teapatest() {
	auto teapatest = RepoProb(0);
	Disciplina d1{ "Matematica",10,"gras","ubb" };
	try {
		teapatest.store(d1);
	}
	catch (BadLuckException& ) {
		assert(true);
		
	}
}



void testeRepo() {
	testAddRepo();
	testAddrepo2();
	testAddrepo3();
	teapatest();
}