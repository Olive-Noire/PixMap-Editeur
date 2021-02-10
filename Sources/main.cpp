#include "./Headers/Class/Editor.hpp"
#include "./Headers/Class/Image.hpp"

#include "./Headers/Functions/Events.hpp"

#include <ctime>

int main(int argc,char* argv[]) {

    srand(time(0));

    Editor editor;
    Image img("test.ppm",{P3,"P3",100,100,255});
    img.Render();

    SDL_Event event;
    do { SDL_PollEvent(&event); UpdateKeys(event); UpdateMouse(event); img.Update(); SDL_RenderPresent(Editor::renderer); } while (event.type != SDL_QUIT);

    return 0;

}