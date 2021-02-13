#ifndef DEF_CONVERT_HPP
#define DEF_CONVERT_HPP

#include <string>
#include <vector>

#include "./Image.hpp"

std::string Convert_PixelsToString(std::vector<std::vector<Pixel>> pixels);
std::vector<std::vector<Pixel>> Convert_StringToPixels(std::string pixels);
std::string Convert_SettingsToString(Settings settings);
Settings Convert_StringToSettings(std::string set);
Pixel Convert_StringToPixel(std::string px);
std::vector<Pixel> Convert_StringToPixelsArray(std::string pxs);
int Convert_StringToNumber(std::string n);

#endif //DEF_CONVERT_HPP