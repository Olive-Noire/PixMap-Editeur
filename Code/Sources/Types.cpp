#include "../Headers/Types.hpp"

std::vector<std::string> Split(std::string s,char c) {

    std::vector<std::string> result;

    for (unsigned int i = 0;i < s.size();i++) {

        if (s[i] == c) {

            std::string t(s);
            result.push_back(t.erase(i,t.size()-1));
            s.erase(s.begin(),s.begin()+i+1);
            i = 0;

        }

    }

    if (s.size() > 0) result.push_back(s);

    for (unsigned int i = 0;i < result.size();i++) {

        for (unsigned int j = 0;j < result[i].size();j++) {
            
            if (result[i][j] == c) result[i].erase(result[i].begin()+j);

        }

        if (result[i] == "") result.erase(result.begin()+i);

    }

    return result;

}

std::string AssemblyStringVector(std::vector<std::string> strings,char c) {

    std::string s("");

    for (unsigned int i = 0;i < strings.size();i++) { s += strings[i]; if (c!='\0') s += c; }

    return s;

}

bool IsNumber(const std::string n)  {
    
    for (char c : n) {

        if (c < '0' || c > '9') { return false; }

    }

    return true;
}

bool VectorPixelHas(std::vector<Pixel*> pxs,Pixel* px) {

    for (unsigned int i = 0;i < pxs.size();i++) if (pxs[i] == px) return true;

    return false;

}

bool EqualColors(Color color1,Color color2) {

    if (color1.red == color2.red &&
        color1.green == color2.green &&
        color1.blue == color2.blue) return true; else return false;

}