#ifndef DEF_FILES_HPP
#define DEF_FILES_HPP

#include <string>
#include <vector>
#include <fstream>

std::string GetContentFile(std::string path);
std::vector<std::string> GetArrayLinesFile(std::string path);
bool ExistingFile(std::string path);
void ClearFile(std::string path);

#endif //DEF_FILES_HPP