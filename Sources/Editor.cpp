#include "../Headers/Editor.hpp"

#include <fstream>

#include "../Headers/Events.hpp"
#include "../Headers/Types.hpp"
#include "../Headers/Button.hpp"

constexpr Button New({255,255,0},{10,5,50,20}),Quit({255,0,0},{70,5,50,20});

SDL_Window* Editor::window;
SDL_Renderer* Editor::renderer;

bool Editor::keys[0x4000011A];
bool Editor::mouses[7];
int Editor::mousePos[4];
Sint8 Editor::wheel;
unsigned int Editor::sensibility;
SDL_Event Editor::event;
Picker* Editor::picker(nullptr);
bool Editor::start;
std::string Editor::version("0.3.0");
std::vector<int> Editor::rendersPerfs,Editor::SavesPerfs,Editor::LoadsPerfs;

Editor::Editor() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

        std::ofstream Debug("Debug.txt",std::ios::app);
        Debug << "X - ERREUR: " << *SDL_GetError() << " - X";
        Debug.close();

    }

    Editor::window = SDL_CreateWindow(("PPM EDITOR " + Editor::version).c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,500,SDL_WINDOW_SHOWN);
    Editor::renderer = SDL_CreateRenderer(window,0,-1);

    start = true;

}

Editor::~Editor() {

    delete img;
    delete picker;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    std::ofstream perfs("./perfsTime.txt");
    perfs << "render : " << Moyenne(rendersPerfs) << "ms\n";
    perfs << "Save : " << Moyenne(SavesPerfs) << "ms\n";
    perfs << "Load : " << Moyenne(LoadsPerfs) << "ms\n";
    perfs.close();

}

void Editor::Open(const std::string &file) {

    img = new Image(file);

}

void Editor::Update() {

    if (((keys[SDLK_LALT] || keys[SDLK_RALT]) && keys[SDLK_F4]) || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)) start = false;

    SDL_WaitEvent(&Editor::event);
    //SDL_PollEvent(&Editor::event);
    UpdateKeys(Editor::event);
    UpdateMouse(Editor::event);
        
    if (img != nullptr) img->Update(); else {

        if (Quit.Hover() && mouses[SDL_BUTTON_LEFT]) start = false;

        if (New.Hover() && mouses[SDL_BUTTON_LEFT]) {

            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        
            Open(std::string(SDL_GetBasePath() + std::string("unamed.ppm")));
            mouses[SDL_BUTTON_LEFT] = false;
        
        }

    }


    if (picker != nullptr) picker->Update();

}

void Editor::Render() const {

    constexpr SDL_Rect MenuBar{0,0,500,30};

    SDL_SetRenderDrawColor(renderer,125,125,125,255);
    SDL_RenderFillRect(renderer,&MenuBar);

    New.Render();
    Quit.Render();

    SDL_RenderPresent(renderer);

    // Interface en préparation...

}