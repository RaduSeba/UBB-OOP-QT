#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class ValidationException {
public:
    explicit ValidationException(const vector<string>& errors) : msg{ errors } {}

    friend ostream& operator<<(ostream& out, const ValidationException& ex);

    vector <string> msg;
};


ostream& operator<<(ostream& out, const ValidationException& ex);

class BadLuckException {
private:
    string msg;
public:
    explicit BadLuckException(const string& str) : msg{ str } {}

    friend ostream& operator<<(ostream& out, const BadLuckException& ex);
};

ostream& operator<<(ostream& out, const BadLuckException& ex);


class Disciplina {
	std::string denumire;
	std::string tip;
	std::string cadru;
	int ore;
public:

	Disciplina() = default;
	Disciplina(const string d, int o, const string t, const string c) :denumire{ d }, ore{ o }, tip{ t }, cadru{ c }{}

	Disciplina(const Disciplina& ot) :denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, cadru{ ot.cadru } {
	}


	string getDenumire() const {
		return denumire;
	}
	int getOre() const noexcept {
		return ore;
	}

	string getTip() const {
		return tip;
	}
	string getCadru() const
	{
		return cadru;
	}

	void setDenumire(string numenou);
	void setOre(int orenoi);
	void setTip(string tipnou);
	void setCadru(string cadrunou);

	bool operator==(const Disciplina& ot);

	Disciplina& operator=(const Disciplina& ot);


};

class Validator {
public:

	static void validate(const string& denumire, const int& ore, const string& tip, const string& cadru);
};


bool has_letters(const string& S);

string toMyString(vector<string> msg);

bool cmpOre(const Disciplina& p1, const Disciplina& p2);

bool cmpDenumire(const Disciplina& p1, const Disciplina& p2);

bool cmpCadruTip(const Disciplina& m1, const Disciplina& m2);


