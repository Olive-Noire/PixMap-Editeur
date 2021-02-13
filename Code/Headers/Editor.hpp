#ifndef DEF_EDITOR_HPP
#define DEF_EDITOR_HPP

#include <SDL.h>
#include <string>

class Image;

#include "./Image.hpp"
#include "./Picker.hpp"

//enum Version {P1 = 1,P2,P3,P4,P5,P6};

class Editor {

    public:
    Editor();
    ~Editor();

    void Open(std::string file);
    void New();

    void Update();
    void Render();

    static SDL_Window* window;
    static SDL_Renderer* renderer;

    static bool keys[0x4000011A];
    static bool mouses[7];
    static int mousePos[4];
    static Sint8 wheel;
    static unsigned char sensibility;
    static SDL_Event event;
    static Picker* picker;
    static bool start;

    protected:
    Image* img;

};

#endif //DEF_EDITOR_HPP