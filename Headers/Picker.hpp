#ifndef DEF_PICKER_HPP
#define DEF_PICKER_HPP

#include <SDL.h>

#include "./Color.hpp"

class Picker final {

    public:
    Picker();
    ~Picker();

    void Update();
    void Render() const;

    inline constexpr Color GetColor() const { return Color{(Uint8)marker.x,(Uint8)marker.y,complementaire}; }
    void SetColor(const Uint8 &r,const Uint8 &g,const Uint8 &b);
    void SetColor(const Color &color);
    void SetColorMod(const bool &color);

    SDL_Window* window;

    protected:
    SDL_Rect marker{0,0,5,5};
    Uint8 complementaire;

    SDL_Renderer* renderer;
    bool colorMod;

};

#endif //DEF_PICKER_HPP