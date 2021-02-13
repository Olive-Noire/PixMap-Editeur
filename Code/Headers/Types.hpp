#ifndef DEF_TYPES_HPP
#define DEF_TYPES_HPP

#include <string>
#include <vector>

#include "./Pixel.hpp"

std::vector<std::string> Split(std::string s,char c);
std::string AssemblyStringVector(std::vector<std::string> strings,char c = '\0');

bool IsNumber(std::string n);
bool VectorPixelHas(std::vector<Pixel*> pxs,Pixel* px);
bool EqualColors(Color color1,Color color2);

#endif //DEF_TYPES_HPP