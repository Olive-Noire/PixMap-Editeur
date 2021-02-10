#ifndef DEF_FUNCTIONS_FILES_HPP
#define DEF_FUNCTIONS_FILES_HPP

#include <string>
#include <vector>
#include <fstream>

std::string GetContentFile(std::string path);
std::vector<std::string> GetArrayLinesFile(std::string path);
bool ExistingFile(std::string path);
void ClearFile(std::string path);
std::vector<std::string> Split(std::string s,char c);
std::string AssemblyStringVector(std::vector<std::string> strings,char c = '\0');

#endif //DEF_FUNCTIONS_FILES_HPP