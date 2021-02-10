#include "../../Headers/Functions/Files.hpp"

std::string GetContentFile(std::string path) {

    std::ifstream file(path);

    std::string content(""),line;

    while (std::getline(file,line)) content += line + "\n";

    file.close();

    return content;

}

std::vector<std::string> GetArrayLinesFile(std::string path) {

    std::ifstream file(path);

    std::string line;
    std::vector<std::string> Lines;

    while (std::getline(file,line)) Lines.push_back(line);

    file.close();

    return Lines;

}

bool ExistingFile(std::string path) {

    std::ifstream file(path);
    bool b = file.good();
    file.close();

    if (GetContentFile(path) == "") return false;

    return b;

}

void ClearFile(std::string path) {

    std::ofstream file(path);
    file << "";
    file.close();

}

std::vector<std::string> Split(std::string s,char c) {

    std::vector<std::string> result;

    for (int i = 0;i < s.size();i++) {

        if (s[i] == c) {

            std::string t(s);
            result.push_back(t.erase(i,t.size()-1));
            s.erase(s.begin(),s.begin()+i+1);
            i = 0;

        }

    }

    if (s.size() > 0) result.push_back(s);

    for (int i = 0;i < result.size();i++) {

        for (int j = 0;j < result[i].size();j++) {
            
            if (result[i][j] == c) result[i].erase(result[i].begin()+j);

        }

        if (result[i] == "") result.erase(result.begin()+i);

    }

    return result;

}

std::string AssemblyStringVector(std::vector<std::string> strings,char c) {

    std::string s("");

    for (int i = 0;i < strings.size();i++) { s += strings[i]; if (c!='\0') s += c; }

    return s;

}