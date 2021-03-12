#ifndef DEF_CLASS_MENU_BUTTON_HPP
#define DEF_CLASS_MENU_BUTTON_HPP

#include <string>

#include "./Color.hpp"

class Button {

    public:
    constexpr Button(const Color &c,const SDL_Rect &r) : color{c}, rect{r} {};

    void Render() const;
    bool Hover() const;

    protected:
    Color color;
    SDL_Rect rect;

};

#endif //DEF_CLASS_MENU_BUTTON_HPP