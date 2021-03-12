#ifndef DEF_IMAGE_HPP
#define DEF_IMAGE_HPP

#include <string>
#include <vector>
#include <fstream>

#include "./Settings.hpp"
#include "./Color.hpp"

class Image final {

    public:
    Image(std::string p = ""/*,Settings s = {P1,"P1",7,10,1}*/);
    ~Image();

    void Save();
    void Render() const;
    void Update();

    void Load(const std::string &p);

    std::string path;
    std::vector<std::vector<Color>> pixels;

    int PixelWidth,PixelHeight;

    protected:
    Settings settings{P3,50,50,255};
    std::ofstream write;
    Color pen{255,255,255};

};

#endif //DEF_IMAGE_HPP