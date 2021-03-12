#ifndef DEF_COLOR_HPP
#define DEF_COLOR_HPP

#include <SDL.h>

struct Color final {

    constexpr Color() : red(0), green(0), blue(0) {}
    constexpr Color(const Uint8 &r, const Uint8 &g, const Uint8 &b) : red{r}, green{g}, blue{b} {}


    constexpr bool operator==(const Color &other) const { 
        return red == other.red &&
               green == other.green &&
               blue == other.blue;
    }

    constexpr bool operator!=(const Color &other) const {
        return red != other.red ||
               green != other.green ||
               blue != other.blue;
    }

    Uint8 red, green, blue;

};

#endif //DEF_COLOR_HPP