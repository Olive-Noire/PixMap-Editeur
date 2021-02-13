#include "../Headers/Files.hpp"

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