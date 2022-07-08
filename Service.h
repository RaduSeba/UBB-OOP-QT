#pragma once

#include "Disciplina.h"
#include "ContractRepo.h"
#include "Undo.h"

#include <string>
#include <vector>

#include <functional>

//#include "Undo.h"

using std::vector;
using std::function;

class ContractService {
private:
	AbsRepo* rep;
	[[maybe_unused]] Validator valid;

	vector<ActiuneUndo*> undoActiuni;



public:
	ContractService(AbsRepo* rep, Validator& val);


	vector<Disciplina>& getAllDiscipline();



	void addDisciplina(const string& denumire, int ore, const string& tip, const string& cadru);
	void	delDisciplina(const int& poz);
	void modifyDisciplina(const int& poz, const string& denumire, const int& ore, const string& tip, const string& cadru);
	
	const Disciplina& cautareDisciplina(const string denumire, const string cadru);



	void filtrareOre(const string& val,vector<Disciplina>& rez);
	void filtrareCadru(const string& val, vector<Disciplina>& rez);


	void sortbyore(vector<Disciplina>& res);
	void sortByDenumire(vector<Disciplina>& res);


	

	int undo();

	~ContractService() = default;


};
void testeService();

