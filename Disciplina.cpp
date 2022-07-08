#include "Disciplina.h"

bool Disciplina::operator==(const Disciplina& ot)
{
	if (denumire == ot.denumire && ore == ot.ore && tip == ot.tip && cadru == ot.cadru)
	{
		return true;
	}
	return false;
}


//Disciplina::Disciplina() {
//	denumire = "";
//	ore = -1;
//	tip = "";
//	cadru = "";
//
//}

Disciplina& Disciplina::operator=(const Disciplina &ot) = default;



bool has_letters(const string& S) {
    for (auto& ch : S) {
        if ('A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z') {
            return true;
        }
    }
    return false;
}

ostream& operator<<(ostream& out, const ValidationException& ex) {
    for (const auto& mess : ex.msg) {
        out << mess << "\n";
    }
    return out;
}

ostream& operator<<(ostream& out, const BadLuckException& ex) {
    out << ex.msg;
    return out;
}

void Validator::validate(
    const string& cnume,
    const int& core,
    const string& ctip,
    const string& ccadru
) {
    //string errors="";

    vector<string> errors;

    bool vname = has_letters(cnume);
    if (cnume.empty()) {
        errors.emplace_back("Numele nu poat fi vid");
    }
    else if (!vname) {
        errors.emplace_back("Numele trebuie sa contina minim o litera");
    }

    bool vprod = has_letters(ctip);
    if (ctip.empty()) {
        errors.emplace_back("Tipul nu poate fi vid");
    }
    else if (!vprod) {
        errors.emplace_back("Tipul trebuie sa contina litere");
    }

    bool vsubst = has_letters(ccadru);
    if (ccadru.empty()) {
        errors.emplace_back("Cadrul nu poate fi vid");
    }
    else if (!vsubst) {
        errors.emplace_back("Cadrul trebuie sa contina litere");
    }

    if (core <= 0) {
        errors.emplace_back("Nr de ore trebuie sa fie un numar natural nenul");
    }
    if (!errors.empty()) {
        throw ValidationException(errors);
    }
}

string toMyString(vector<string> msg) {
    string ans = "";
    for (const auto& mg : msg) {
        ans += mg;
        ans += "\n";
    }
    return ans;
}

bool cmpDenumire(const Disciplina& p1, const Disciplina& p2)
{
    return p1.getDenumire() < p2.getDenumire();
}

bool cmpOre(const Disciplina& p1, const Disciplina& p2)
{
    return p1.getOre() < p2.getOre();
}

bool cmpCadruTip(const Disciplina& m1, const Disciplina& m2) {
    if (m1.getCadru() == m2.getCadru())
        return m1.getDenumire() < m2.getDenumire();
    else
        return m1.getTip() < m2.getTip();
}