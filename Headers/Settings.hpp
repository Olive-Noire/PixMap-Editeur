#ifndef DEF_SETTINGS_HPP
#define DEF_SETTINGS_HPP

enum Version {P1 = 1,P2,P3,P4,P5,P6};

struct Settings final {

    Version version;
    int sizeX;
    int sizeY;
    int maxColor;

    constexpr bool operator==(const Settings &other) const {

        return version == other.version &&
               sizeX == other.sizeX &&
               sizeY == other.sizeY &&
               maxColor == other.maxColor;
    }

    constexpr bool operator!=(const Settings &other) const {

        return version != other.version ||
               sizeX != other.sizeX ||
               sizeY != other.sizeY ||
               maxColor != other.maxColor;
    }

};

#endif //DEF_SETTINGS_HPP