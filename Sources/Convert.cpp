#include "../Headers/Convert.hpp"

#include <sstream>
#include <iostream>

//#include "../Headers/Files.hpp"
#include "../Headers/Types.hpp"

std::string Convert_PixelsArraysToString(const std::vector<std::vector<Color>> &pixels,const Version &v) {

    std::vector<std::string> linesRange;

    for (unsigned int i = 0;i < pixels.size();i++) {

        for (unsigned int j = 0;j < pixels[i].size();j++) {
            
            if (v == Version::P3) { 
                
                linesRange.push_back(std::to_string(pixels[j][i].red)+" "+std::to_string(pixels[j][i].green)+" "+std::to_string(pixels[j][i].blue)+" ");
                
            } else if (v == Version::P2) {

                linesRange.push_back(std::to_string((pixels[j][i].red+pixels[j][i].green+pixels[j][i].blue)/3) + " ");

            } else if (v == Version::P1) {

                linesRange.push_back(std::to_string(pixels[j][i].red) + " ");

            }

        }

        if (i < pixels.size()-1) linesRange.push_back("\n");
    }


    return AssemblyStringVector(linesRange);

}

std::vector<std::vector<Color>> Convert_StringToPixelsArrays(const std::string &pixels,const Version &v) {

    std::vector<std::vector<Color>> pxs;
    std::vector<std::string> lines(Split(pixels,'\n')),linesRange;
    const Settings &settings = Convert_StringToSettings(lines[0]);
    lines.erase(lines.begin());

    for (unsigned int i(0);i < lines.size();i++) {

        
        for (unsigned int j(0);j < (unsigned int)settings.sizeY;j++) {
            
            const std::vector<std::string> &line(Split(lines[j],' '));
            if (v == Version::P3) linesRange.push_back(line[i*3]+" "+line[1+i*3]+" "+line[2+i*3]); else {
                
                const std::vector<std::string> &line(Split(lines[j],' '));
                linesRange.push_back(line[i]);

            }

        }

        if (v == Version::P3) pxs.push_back(Convert_StringToPixelsLine(AssemblyStringVector(linesRange,' '))); else pxs.push_back(Convert_StringToPixelsLine(AssemblyStringVector(linesRange,' '),false));
        linesRange.clear();

    }

    return pxs;

}

std::string Convert_SettingsToString(const Settings &settings) {

    return Convert_VersionToString(settings.version) + " " + std::to_string(settings.sizeX) + " " + std::to_string(settings.sizeY) + " " + std::to_string(settings.maxColor) + "\n";

}

Settings Convert_StringToSettings(const std::string &s) {

    const std::vector<std::string> &set(Split(s,' '));
    if (set.size() < 4) return Settings{P1,0,0,1};

    //Verifie si c'est pas un P1 pour ne pas ajouter un argument
    if (set[0].back() != '1') {

        const int &x(Convert_StringToNumber(set[1])),&y(Convert_StringToNumber(set[2])),&c(Convert_StringToNumber(set[3]));
        return {(Version)Convert_StringToNumber({set[0].back()}),x,y,c};

    } else {

        const int &x(Convert_StringToNumber(set[1])),&y(Convert_StringToNumber(set[2]));
        return {(Version)Convert_StringToNumber({set[0].back()}),x,y,1};

    }

}

Color Convert_StringToPixel(const std::string &px,const bool &color) {

    if (color) {

        const std::vector<std::string> &s(Split(px,' '));
        return Color(Convert_StringToNumber(s[0]),Convert_StringToNumber(s[1]),Convert_StringToNumber(s[2]));

    } else {

        const Uint8 &c = Convert_StringToNumber(px);
        return Color(c,c,c);

    }

}

std::vector<Color> Convert_StringToPixelsLine(const std::string &pxs,const bool &color) {

    const std::vector<std::string> &s(Split(pxs,' '));
    std::vector<std::string> pxsLines;
    std::vector<Color> pixels;

    if (color) {

        for (unsigned int i(0);2+i*3 < s.size();i++) { pxsLines.push_back(s[i*3]+" "+s[1+i*3]+" "+s[2+i*3]); }
        for (unsigned int i(0);i < pxsLines.size();i++) pixels.push_back(Convert_StringToPixel(pxsLines[i]));

    } else {

        for (unsigned int i(0);i < s.size();i++) { pxsLines.push_back(s[i]); }
        for (unsigned int i(0);i < pxsLines.size();i++) pixels.push_back(Convert_StringToPixel(pxsLines[i],false));

    }

    return pixels;

}

int Convert_StringToNumber(const std::string &n) {

    if (IsNumber(n)) {

        int nbr;
        std::stringstream ss(n);
        ss >> nbr;
        return nbr;

    } else return 0;

}

std::string Convert_VersionToString(const Version &v) {

    if (v == Version::P1) return "P1";
    if (v == Version::P2) return "P2";
    if (v == Version::P3) return "P3";
    if (v == Version::P4) return "P4";
    if (v == Version::P5) return "P5";
    if (v == Version::P6) return "P6";

    return "";

}