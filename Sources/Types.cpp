#include "../Headers/Types.hpp"

std::vector<std::string> Split(std::string s,const char &c) {

    std::vector<std::string> result;

    for (unsigned int i(0);i < s.size();i++) {

        if (s[i] == c) {

            std::string t(s);
            result.push_back(t.erase(i,t.size()-1));
            s.erase(s.begin(),s.begin()+i+1);
            i = 0;

        }

    }

    if (s.size() > 0) result.push_back(s);

    for (unsigned int i(0);i < result.size();i++) {

        for (unsigned int j(0);j < result[i].size();j++) {
            
            if (result[i][j] == c) result[i].erase(result[i].begin()+j);

        }

        if (result[i] == "") result.erase(result.begin()+i);

    }

    return result;

}

std::string AssemblyStringVector(const std::vector<std::string> &strings,const char &c) {

    std::string s("");
    for (unsigned int i = 0;i < strings.size();i++) { s += strings[i]; if (c!='\0') s += c; }

    return s;

}

bool IsNumber(const std::string &n)  {
    
    for (const char &c : n) {

        if (c < '0' || c > '9') return false;

    }

    return true;
}

bool VectorColorHas(const std::vector<Color> &pxs,const Color &px) {

    for (const Color &p : pxs) if (&p == &px) return true;

    return false;

}

int Moyenne(const std::vector<int> &donnees) {

    if (donnees.size() == 0) return donnees.size();

    int resultat(0);
    for (unsigned int i : donnees) resultat+=(int)i;
    return resultat/donnees.size();

}