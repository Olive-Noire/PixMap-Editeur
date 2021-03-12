#include "../Headers/Files.hpp"

std::string GetContentFile(const std::string &path) {

    std::ifstream file(path);

    std::string content(""),line;

    while (std::getline(file,line)) content += line + "\n";

    file.close();

    return content;

}

std::vector<std::string> GetArrayLinesFile(const std::string &path) {

    std::ifstream file(path);

    std::string line;
    std::vector<std::string> Lines;

    while (std::getline(file,line)) Lines.push_back(line);

    file.close();

    return Lines;

}

bool ExistingFile(const std::string &path) {

    std::ifstream file(path);
    const bool &b = file.good();
    file.close();

    if (GetContentFile(path) == "") return false; else return b;

}

void ClearFile(const std::string &path) {

    std::ofstream file(path);
    file << "";
    file.close();

}

int GetNumberLinesFiles(const std::string &path) {

    if (ExistingFile(path)) {

        std::ifstream file(path);
        std::string s("");

        int n(0);
        while (std::getline(file,s)) { n++; }

        file.close();

        return n;

    } else return 0;

}