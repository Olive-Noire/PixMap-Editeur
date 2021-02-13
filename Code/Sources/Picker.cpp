#include "../Headers/Picker.hpp"

#include "../Headers/Editor.hpp"

Picker::Picker() {

    window = SDL_CreateWindow("PPM EDITOR - Color Picker",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,765,255,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,0,-1);

    marker = {0,0,5,5};
    current = {510,50,50,50};
    complementaireBar = {382,200,255,10};
    cursor = {382,190,30,30};

    complementaire = 0;

    Render();

}

Picker::~Picker() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

void Picker::Render() {

    SDL_RenderClear(renderer);

    for (unsigned int i = 0;i < 255;i++) {

        for (unsigned int j = 0;j < 255;j++) {

            SDL_SetRenderDrawColor(renderer,i,j,complementaire,255);
            SDL_RenderDrawPoint(renderer,i,j);

        }

    }

    SDL_SetRenderDrawColor(renderer,120,120,120,255);
    SDL_RenderFillRect(renderer,&marker);

    SDL_SetRenderDrawColor(renderer,marker.x,marker.y,complementaire,255);
    SDL_RenderFillRect(renderer,&current);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&complementaireBar);

    SDL_SetRenderDrawColor(renderer,0,0,255,255);
    SDL_RenderFillRect(renderer,&cursor);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderPresent(renderer);

}

void Picker::Update() {

    unsigned int id = SDL_GetWindowID(this->window);
    bool enter(id == Editor::event.window.windowID);

    if (Editor::keys[SDLK_RIGHT] && complementaire < 255 && enter) {

        cursor.x++;
        complementaire = cursor.x-382;
        Render();

    }

    if (Editor::keys[SDLK_LEFT] && complementaire > 0 && enter) {

        cursor.x--;
        complementaire = cursor.x-382;
        Render();

    }

    if (Editor::mouses[SDL_BUTTON_LEFT] && enter) {

        if (Editor::mousePos[0] < 255 && Editor::mousePos[1] < 255) {

            marker.x = Editor::mousePos[0];
            marker.y = Editor::mousePos[1];
            Render();

        }

        if (complementaireBar.x <= Editor::mousePos[0] && complementaireBar.y <= Editor::mousePos[1] && complementaireBar.x + complementaireBar.w >= Editor::mousePos[0] && complementaireBar.y + complementaireBar.h >= Editor::mousePos[1]) {

            cursor.x = Editor::mousePos[0];
            complementaire = cursor.x-382;
            Render();

        }

    }

}

Color Picker::GetColor() {

    return {marker.x,marker.y,complementaire};

}

void Picker::SetColor(unsigned char r,unsigned char g,unsigned char b) {

    marker.x = (int)r;
    marker.y = (int)g;
    complementaire = b;
    cursor.x = 382+complementaire;

    Render();

}

void Picker::SetColor(Color color) {

    marker.x = color.red;
    marker.y = color.green;
    cursor.x = 382+color.blue;

    complementaire = cursor.x-382;

    Render();

}