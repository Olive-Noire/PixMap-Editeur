#include "../../Headers/Class/Editor.hpp"

#include <fstream>

SDL_Window* Editor::window;
SDL_Renderer* Editor::renderer;

bool Editor::keys[0x4000011A];
bool Editor::mouses[7];
int Editor::mousePos[4];
Sint8 Editor::wheel;
unsigned char Editor::sensibility;

Editor::Editor() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

        std::ofstream Debug("Debug.txt",std::ios::app);
        Debug << "X - ERREUR: " << *SDL_GetError() << " - X";

    }

    Editor::window = SDL_CreateWindow("PPM EDITOR 0.0.1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,500,SDL_WINDOW_SHOWN);
    Editor::renderer = SDL_CreateRenderer(window,0,-1);

}

Editor::~Editor() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

}