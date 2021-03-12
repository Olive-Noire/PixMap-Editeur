#ifndef DEF_FILES_HPP
#define DEF_FILES_HPP

#include <string>
#include <vector>
#include <fstream>

std::string GetContentFile(const std::string &path);
std::vector<std::string> GetArrayLinesFile(const std::string &path);
bool ExistingFile(const std::string &path);
void ClearFile(const std::string &path);
int GetNumberLinesFiles(const std::string &path);

#endif //DEF_FILES_HPP