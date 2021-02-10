#ifndef DEF_CLASS_EDITOR_HPP
#define DEF_CLASS_EDITOR_HPP

#include <SDL.h>
#include <string>

enum Version {P1 = 1,P2,P3,P4,P5};

class Editor {

    public:
    Editor();
    ~Editor();

    void OpenFile(std::string file);

    static SDL_Window* window;
    static SDL_Renderer* renderer;

    static bool keys[0x4000011A];
    static bool mouses[7];
    static int mousePos[4];
    static Sint8 wheel;
    static unsigned char sensibility;

    protected:

};

#endif //DEF_CLASS_EDITOR_HPP