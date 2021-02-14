#ifndef DEF_PICKER_HPP
#define DEF_PICKER_HPP

#include <SDL.h>

#include "./Pixel.hpp"

class Picker {

    public:
    Picker();
    ~Picker();

    void Update();
    void Render();

    Color GetColor();
    void SetColor(unsigned char r,unsigned char g,unsigned char b);
    void SetColor(Color color);

    SDL_Window* window;

    protected:
    SDL_Rect marker,current,complementaireBar,cursor;
    unsigned char complementaire;

    SDL_Renderer* renderer;

};

#endif //DEF_PICKER_HPP