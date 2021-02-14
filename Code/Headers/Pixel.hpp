#ifndef DEF_PIXEL_HPP
#define DEF_PIXEL_HPP

#include <SDL.h>

struct Color { Uint8 red,green,blue; };

class Pixel {

    public:
    Pixel(int r,int g,int b);
    ~Pixel() = default;

    SDL_Rect rect{0,0,0,0};
    Color color;

};

#endif //DEF_PIXEL_HPP