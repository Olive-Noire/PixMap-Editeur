#include "../Headers/Editor.hpp"

#include <fstream>

#include "../Headers/Events.hpp"

SDL_Window* Editor::window;
SDL_Renderer* Editor::renderer;

bool Editor::keys[0x4000011A];
bool Editor::mouses[7];
int Editor::mousePos[4];
Sint8 Editor::wheel;
unsigned char Editor::sensibility;
SDL_Event Editor::event;
Picker* Editor::picker;
bool Editor::start;

Editor::Editor() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

        std::ofstream Debug("Debug.txt",std::ios::app);
        Debug << "X - ERREUR: " << *SDL_GetError() << " - X";
        Debug.close();

    }

    Editor::window = SDL_CreateWindow("PPM EDITOR 0.0.1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,500,SDL_WINDOW_SHOWN);
    Editor::renderer = SDL_CreateRenderer(window,0,-1);
    picker = new Picker();

    start = true;

}

Editor::~Editor() {

    delete img;
    delete picker;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

}

void Editor::Open(std::string file) {

    img = new Image(file);

}

void Editor::New() {

    img = new Image(std::string(SDL_GetBasePath()) + std::string("unamed.ppm"));

}

void Editor::Update() {

    if (((keys[SDLK_LALT] || keys[SDLK_RALT]) && keys[SDLK_F4]) || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)) start = false;

    SDL_PollEvent(&Editor::event);
    UpdateKeys(Editor::event);
    UpdateMouse(Editor::event);
        
    img->Update();
    picker->Update();

}

void Editor::Render() {

    // Interface en préparation...

}