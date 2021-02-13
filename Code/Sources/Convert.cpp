#include "../Headers/Convert.hpp"

#include <sstream>
#include <iostream>

#include "../Headers/Files.hpp"
#include "../Headers/Types.hpp"

std::string Convert_PixelsToString(std::vector<std::vector<Pixel>> pixels) {

    std::vector<std::string> linesRange;

    for (unsigned int i = 0;i < pixels.size();i++) {

        for (unsigned int j = 0;j < pixels[i].size();j++) {
            
            linesRange.push_back(std::to_string(pixels[j][i].color.red)+" "+std::to_string(pixels[j][i].color.green)+" "+std::to_string(pixels[j][i].color.blue)+" ");

        }

        if (i < pixels.size()-1) linesRange.push_back("\n");
    }

    return AssemblyStringVector(linesRange);

}

std::vector<std::vector<Pixel>> Convert_StringToPixels(std::string pixels) {

    std::vector<std::vector<Pixel>> pxs;

    std::vector<std::string> lines(Split(pixels,'\n'));
    Settings settings = Convert_StringToSettings(lines[0]);
    lines.erase(lines.begin());

    std::vector<std::string> linesRange;

    for (unsigned int i = 0;i < lines.size();i++) {

        
        for (int j = 0;j < settings.sizeY;j++) {
            
            std::vector<std::string> line = Split(lines[j],' ');
            linesRange.push_back(line[i*3]+" "+line[1+i*3]+" "+line[2+i*3]);
            //linesRange.push_back(line[j*3]+" "+line[1+j*3]+" "+line[2+j*3]);

        }
        

        pxs.push_back(Convert_StringToPixelsArray(AssemblyStringVector(linesRange,' ')));

       linesRange.clear();

    }

    return pxs;

}

std::string Convert_SettingsToString(Settings settings) {

    return settings.name + " " + std::to_string(settings.sizeX) + " " + std::to_string(settings.sizeY) + " " + std::to_string(settings.maxColor) + "\n";

}

Settings Convert_StringToSettings(std::string s) {

    std::vector<std::string> set(Split(s,' '));
    if (set.size() < 4) return {P1,"P1",0,0,0};

    int x(Convert_StringToNumber(set[1])),y(Convert_StringToNumber(set[2])),c(Convert_StringToNumber(set[3]));
    return {P3,"P3",x,y,c};

}

Pixel Convert_StringToPixel(std::string px) {

    std::vector<std::string> s(Split(px,' '));
    return *(new Pixel(Convert_StringToNumber(s[0]),Convert_StringToNumber(s[1]),Convert_StringToNumber(s[2])));

}

std::vector<Pixel> Convert_StringToPixelsArray(std::string pxs) {

    std::vector<std::string> s(Split(pxs,' ')),pxsLines;
    std::vector<Pixel> pixels;
    for (unsigned int i = 0;i*3 < s.size();i++) pxsLines.push_back(s[i*3]+" "+s[1+i*3]+" "+s[2+i*3]+" ");
    for (unsigned int i = 0;i < pxsLines.size();i++) pixels.push_back(Convert_StringToPixel(pxsLines[i]));

    return pixels;

}

int Convert_StringToNumber(std::string n) {

    if (IsNumber(n)) {

        int nbr;
        std::stringstream ss(n);
        ss >> nbr;
        return nbr;

    } else return 0;

}