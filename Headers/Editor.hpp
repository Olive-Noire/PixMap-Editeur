#ifndef DEF_EDITOR_HPP
#define DEF_EDITOR_HPP

#include <SDL.h>
#include <string>
#include <vector>

#include "./Picker.hpp"
#include "./Image.hpp"
//#include "./Tool.hpp"

class Editor {

    public:
    Editor();
    ~Editor();

    void Open(const std::string &file);

    void Update();
    void Render() const;

    static SDL_Window* window;
    static SDL_Renderer* renderer;

    static bool keys[0x4000011A],mouses[7],start;
    static int mousePos[4];
    static Sint8 wheel;
    static unsigned int sensibility;
    static SDL_Event event;
    static Picker* picker;
    static std::string version;
    static std::vector<int> rendersPerfs,SavesPerfs,LoadsPerfs;

    Image* img{nullptr};

};

#endif //DEF_EDITOR_HPP