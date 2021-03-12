#ifndef DEF_TYPES_HPP
#define DEF_TYPES_HPP

#include <string>
#include <vector>

#include "./Picker.hpp"

std::vector<std::string> Split(std::string s,const char &c);
std::string AssemblyStringVector(const std::vector<std::string> &strings,const char &c = '\0');

bool IsNumber(const std::string &n);
bool VectorColorHas(const std::vector<Color> &pxs,const Color &px);

int Moyenne(const std::vector<int> &donnees);

#endif //DEF_TYPES_HPP