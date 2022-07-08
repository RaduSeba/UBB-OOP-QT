#include "Service.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <memory>


ContractService::ContractService(AbsRepo* rp, Validator& vl) {
	rep = rp;
	valid = vl;
	undoActiuni.clear();
}


vector<Disciplina>& ContractService::getAllDiscipline() {
	return rep->getAllDiscipline();
}







void ContractService::addDisciplina(const string& denumire, int ore, const string& tip, const string& cadru) {
	
	Validator::validate(denumire, ore, tip, cadru);
	
	auto d=Disciplina( denumire,ore,tip,cadru );
	auto& v = rep->getAllDiscipline();
	vector<string> err;
	for (auto& it : v) {
		if (it == d) {
			err.emplace_back("Element deja existent");
		}
	}
	if (!err.empty()) {
		throw ContractRepoException(err);
	}
	rep->store(d);
	undoActiuni.push_back(new undoAdauga(rep, d));
}






void ContractService::delDisciplina(const int& poz) {


	vector<string> err;

	if (poz < 0 || poz >= rep->getAllDiscipline().size()) {
		err.emplace_back("Pozitie invalida");
		throw ContractRepoException(err);
	}
	auto dlt = rep->getAllDiscipline()[poz];
	rep->delet(poz);
	undoActiuni.push_back(new undoSterge (rep, dlt, poz));

}

void ContractService::modifyDisciplina(const int& poz, const string& denumire, const int& ore, const string& tip, const string& cadru) {
	Validator::validate(denumire, ore, tip, cadru);
	vector<string> err;
	if (poz < 0 || poz >= rep->getAllDiscipline().size()) {
		err.emplace_back("Pozitie invalida");
		throw ContractRepoException(err);
	}
	//const Disciplina disciplinademodificat = rep->find(denumire,cadru);

	auto di = rep->getAllDiscipline()[poz];
	rep->modifica(Disciplina(denumire,ore,tip,cadru), poz);
	undoActiuni.push_back(new undoUpdate(rep, di, poz));
}


void ContractService::filtrareOre(const string& val, vector<Disciplina>& rez) {
	vector <string> err;
	int ore = 0;
	bool vld = true;
	for (auto& ch : val) {
		if ('0' <= ch && ch <= '9') {
			ore = ore * 10 + (ch - '0');

		}
		else {
			vld = false;
		}

	}
	if (!vld) {
		err.emplace_back("Nr ore invalid");
		throw ContractRepoException(err);
	}
	rez.clear();
	copy_if(rep->getAllDiscipline().begin(), rep->getAllDiscipline().end(), back_inserter(rez), [=](Disciplina& d) {
		return d.getOre() == ore;
		});
	return;
}


void ContractService::filtrareCadru(const string& val, vector<Disciplina>& rez) {
	rez.clear();
	copy_if(rep->getAllDiscipline().begin(), rep->getAllDiscipline().end(), back_inserter(rez), [=](Disciplina& d) {
		return d.getCadru() == val;
		});
	return;
}



void ContractService::sortbyore(vector<Disciplina>& res)
{
	res = rep->getAllDiscipline();
	sort(res.begin(), res.end(), cmpOre);
}

void ContractService::sortByDenumire(vector<Disciplina>& res) {
	res = rep->getAllDiscipline();
	sort(res.begin(), res.end(), cmpDenumire);
}

int ContractService::undo()
{
	if (undoActiuni.empty())
		return -1;

	ActiuneUndo* act = undoActiuni.back();
	act->doUndo();
	undoActiuni.pop_back();
	delete act;
	return 0;
}



//ContractService::~ContractService()
//{
//	delete this->rep;
//}








void testAddService() {
	auto* testRepo = new ContractRepo();
	auto testVal = Validator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("oop", 5, "de", "fsega");
	testService.addDisciplina("oop2", 5, "de", "fsega2");
	testService.addDisciplina("oop3", 5, "de", "fsega3");

	assert(testService.getAllDiscipline().size() == 3);

	try {
		testService.addDisciplina("oop", 5, "de", "fsega");
	}
	catch (ContractRepoException&) {
		assert(true);
	}


	


	testService.delDisciplina(0);


	testService.modifyDisciplina(1, "oop2", 23, "2sas", "fsega2");



}



void testContract() {
	auto* testRepo = new ContractRepo();
	auto testVal = Validator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("oop", 5, "de", "fsega");
	testService.addDisciplina("so", 3, "sas", "ubb");
	testService.addDisciplina("stefan", 22, "sirb", "ubb");
	testService.addDisciplina("seba", 212, "sssa", "fsega");

	



}

void testSortService() {
	auto* testRepo = new ContractRepo();
	auto testVal = Validator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("so", 3, "sas", "ubb");
	testService.addDisciplina("stefan", 22, "sirb", "ubb");
	testService.addDisciplina("seba", 212, "sssa", "fsega");
	testService.addDisciplina("oop", 5, "de", "fsega");

	/*vector<Disciplina> sortedByOre = testService.sortByOre();
	assert(sortedByOre[0].getDenumire() == "so");
	assert(sortedByOre[1].getDenumire() == "oop");
	assert(sortedByOre[2].getDenumire() == "stefan");*/


	/*vector<Disciplina> sortedByDenumire = testService.sortByDenumire();
	assert(sortedByDenumire[0].getCadru() == "fsega");
	assert(sortedByDenumire[0].getDenumire() == "oop");*/





}



void testeService() {
	testAddService();
	
	testContract();
	testSortService();
}
