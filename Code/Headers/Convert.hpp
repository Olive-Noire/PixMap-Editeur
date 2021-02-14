#ifndef DEF_CONVERT_HPP
#define DEF_CONVERT_HPP

#include <string>
#include <vector>

#include "./Image.hpp"

std::string Convert_PixelsArraysToString(std::vector<std::vector<Pixel>> pixels);
std::vector<std::vector<Pixel>> Convert_StringToPixelsArrays(std::string pixels);
std::string Convert_SettingsToString(Settings settings);
Settings Convert_StringToSettings(std::string set);
Pixel Convert_StringToPixel(std::string px);
std::vector<Pixel> Convert_StringToPixelsLine(std::string pxs);
int Convert_StringToNumber(std::string n);

#endif //DEF_CONVERT_HPP