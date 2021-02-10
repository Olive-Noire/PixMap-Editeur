#ifndef DEF_CLASS_IMAGE_HPP
#define DEF_CLASS_IMAGE_HPP

#include "./Pixel.hpp"
#include "./Editor.hpp"

#include <string>
#include <vector>
#include <fstream>

struct Settings {

    Version version;
    std::string name;
    unsigned short sizeX;
    unsigned short sizeY;
    unsigned short maxColor;

};

class Image {

    public:
    Image(std::string p = "",Settings s = {P3,"P3",50,50,255});
    ~Image();

    void Save();
    void Render();
    void Update();

    void Load(std::string p);

    protected:
    Settings settings;
    std::vector<std::vector<Pixel>> pixels;
    int background[3]{NULL,NULL,NULL};
    std::ofstream write;
    std::ifstream read;
    std::string content{};
    std::string path;
    Color pen{255,255,255};

};

#endif //DEF_CLASS_IMAGE_HPP