#ifndef DEF_CLASS_PIXEL_HPP
#define DEF_CLASS_PIXEL_HPP

#include <SDL.h>

struct Color { int red,green,blue; };

class Pixel {

    public:
    Pixel(int r,int g,int b);
    ~Pixel() = default;

    SDL_Rect rect{NULL,NULL,NULL,NULL};
    Color color;

};

#endif //DEF_CLASS_PIXEL_HPP