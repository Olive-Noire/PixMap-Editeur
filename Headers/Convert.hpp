#ifndef DEF_CONVERT_HPP
#define DEF_CONVERT_HPP

#include <string>
#include <vector>

#include "./Settings.hpp"
#include "./Color.hpp"

std::string Convert_PixelsArraysToString(const std::vector<std::vector<Color>> &pixels,const Version &v);
std::vector<std::vector<Color>> Convert_StringToPixelsArrays(const std::string &pixels,const Version &v);
std::string Convert_SettingsToString(const Settings &settings);
Settings Convert_StringToSettings(const std::string &set);
Color Convert_StringToPixel(const std::string &px,const bool &color = true);
std::vector<Color> Convert_StringToPixelsLine(const std::string &pxs,const bool &color = true);
std::string Convert_VersionToString(const Version &v);
int Convert_StringToNumber(const std::string &n);

#endif //DEF_CONVERT_HPP