#ifndef DEF_PIXEL_HPP
#define DEF_PIXEL_HPP

#include <SDL.h>

struct Color { int red,green,blue; };

class Pixel {

    public:
    Pixel(int r,int g,int b);
    ~Pixel() = default;

    SDL_Rect rect{0,0,0,0};
    Color color;

};

#endif //DEF_PIXEL_HPP