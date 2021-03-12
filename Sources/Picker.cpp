#include "../Headers/Picker.hpp"

#include "../Headers/Editor.hpp"

SDL_Rect complementaireBar{0,200,255,10},cursor{-30,190,30,30};

Picker::Picker() {

    window = SDL_CreateWindow(("PPM EDITOR " + Editor::version + " - Color Picker").c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,765,255,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,0,-1);

    complementaire = 0;

    Render();

}

Picker::~Picker() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

void Picker::Render() const {

    SDL_RenderClear(renderer);

    if (colorMod) {

        complementaireBar.x = 382;
        constexpr SDL_Rect current{510,50,50,50};

        for (unsigned int i(0);i < 255;i++) {

            for (unsigned int j(0);j < 255;j++) {

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

    } else {

        complementaireBar.x = 255;
        constexpr SDL_Rect current{357,50,50,50};

        SDL_SetRenderDrawColor(renderer,marker.x,marker.y,complementaire,255);
        SDL_RenderFillRect(renderer,&current);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer,&complementaireBar);

        SDL_SetRenderDrawColor(renderer,0,0,255,255);
        SDL_RenderFillRect(renderer,&cursor);

    }

    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderPresent(renderer);

}

void Picker::Update() {

    const unsigned int &id = SDL_GetWindowID(this->window);
    const bool &enter(id == Editor::event.window.windowID);

    if (Editor::keys[SDLK_RIGHT] && complementaire < 255 && enter) {

        cursor.x++;
        if (colorMod) complementaire = cursor.x-382; else marker.x = marker.y = complementaire = cursor.x-255;
        Render();

    }

    if (Editor::keys[SDLK_LEFT] && complementaire > 0 && enter) {

        cursor.x--;
        if (colorMod) complementaire = cursor.x-382; else marker.x = marker.y = complementaire = cursor.x-255;
        Render();

    }

    if (Editor::mouses[SDL_BUTTON_LEFT] && enter) {

        if (Editor::mousePos[0] < 255 && Editor::mousePos[1] < 255 && colorMod) {

            marker.x = Editor::mousePos[0];
            marker.y = Editor::mousePos[1];
            Render();

        }

        if (complementaireBar.x <= Editor::mousePos[0] && complementaireBar.y <= Editor::mousePos[1] && complementaireBar.x + complementaireBar.w >= Editor::mousePos[0] && complementaireBar.y + complementaireBar.h >= Editor::mousePos[1]) {

            cursor.x = Editor::mousePos[0];
            if (colorMod) complementaire = cursor.x-382; else marker.x = marker.y = complementaire = cursor.x-255;
            Render();

        }

    }

}
void Picker::SetColor(const Uint8 &r,const Uint8 &g,const Uint8 &b) {

    marker.x = r;
    marker.y = g;
    complementaire = b;
    if (colorMod) cursor.x = 382+complementaire; else cursor.x = 255+complementaire;

    Render();

}

void Picker::SetColor(const Color &color) {

    marker.x = color.red;
    marker.y = color.green;
    cursor.x = 382+color.blue;

    if (colorMod) complementaire = cursor.x-382; else complementaire = cursor.x-255;

    Render();

}

void Picker::SetColorMod(const bool &color) {

    colorMod = color;
    if (color) cursor.x = 382; else cursor.x = 255;

}