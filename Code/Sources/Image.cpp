#include "../Headers/Image.hpp"

#include <iostream>

#include "../Headers/Convert.hpp"
#include "../Headers/Files.hpp"
#include "../Headers/Editor.hpp"
#include "../Headers/Types.hpp"

Image::Image(std::string p,Settings s) {

    settings = s;
    Load(p);

}

Image::~Image() {

    write.close();
    read.close();

}

void Image::Save() {

    write.open(path);
    write << content;
    write.close();
    SDL_SetWindowTitle(Editor::window,("PPM EDITOR 0.0.1 - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1]).c_str());

}

void Image::Render() {

    int width,height;
    SDL_GetRendererOutputSize(Editor::renderer,&width,&height);

    unsigned int PixelWidth(width/pixels.size()),PixelHeight(height/pixels[0].size());

    for (unsigned int i = 0;i < pixels.size();i++) {

        for (unsigned int j = 0;j < pixels[i].size();j++) {

            pixels[i][j].rect = {(int)(i*PixelWidth),(int)(j*PixelHeight),(int)PixelWidth,(int)PixelHeight};

            SDL_SetRenderDrawColor(Editor::renderer,pixels[i][j].color.red,pixels[i][j].color.green,pixels[i][j].color.blue,255);
            SDL_RenderFillRect(Editor::renderer,&pixels[i][j].rect);

        }

    }

    SDL_SetRenderDrawColor(Editor::renderer,0,0,0,0);
    SDL_RenderPresent(Editor::renderer);

}

void Image::Update() {

    Editor::picker->Update();

    pen = Editor::picker->GetColor();

    unsigned int id = SDL_GetWindowID(Editor::window);
    bool enter(id == Editor::event.window.windowID);

    int hover_x(Editor::mousePos[0]/pixels[0][0].rect.w),hover_y(Editor::mousePos[1] / pixels[0][0].rect.h);
    Pixel* px = &pixels[hover_x][hover_y];

    //if (Editor::keys[SDLK_LSHIFT] && enter) form_base = px;

    if (Editor::keys[SDLK_LCTRL] && Editor::keys[SDLK_s]) {
        
        content = Convert_SettingsToString(settings) + Convert_PixelsToString(pixels);
        pixels = Convert_StringToPixels(content);
        Save();
        Render();

        Editor::keys[SDLK_LCTRL] = false;
    
    }

    //std::cout << "state : " << Editor::mouses[SDL_BUTTON_LEFT] << std::endl;

    if (Editor::mouses[SDL_BUTTON_LEFT] && enter) {

        if (!EqualColors(px->color,pen)) {

            px->color = pen;
            Render();
            SDL_SetWindowTitle(Editor::window,("PPM EDITOR 0.2.0 - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1] + " *").c_str());

        }

    }

    if (Editor::mouses[SDL_BUTTON_RIGHT] && enter) {

        if (!EqualColors(px->color,{0,0,0})) {

            px->color = {0,0,0};
            Render();
            SDL_SetWindowTitle(Editor::window,("PPM EDITOR 0.2.0 - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1] + " *").c_str());

        }

    }

    if (Editor::keys[SDLK_v]) {

        std::cout << content << std::endl;

        Editor::keys[SDLK_v] = false;

    }

    if (Editor::keys[SDLK_c]) {

        for (unsigned int i = 0;i < pixels.size();i++) {

            for (unsigned int j = 0;j < pixels[i].size();j++) {

                if (!EqualColors(pixels[i][j].color,{0,0,0})) pixels[i][j].color = {0,0,0};

            }

        }

        Render();
        SDL_SetWindowTitle(Editor::window,("PPM EDITOR 0.2.0 - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1] + " *").c_str());

        Editor::keys[SDLK_c] = false;

    }

    /*
    if (Editor::keys[SDLK_r] && enter) {

        if (form_base != nullptr) {

            form_base->color = pen;
            for (int i = 0;i < px->rect.x/px->rect.w - form_base->rect.x/form_base->rect.w;i++) pixels[hover_x+i][form_base->rect.y/form_base->rect.h+i].color = pen;
            for (int i = 0;i < px->rect.y/px->rect.h - form_base->rect.y/form_base->rect.h;i++) pixels[form_base->rect.x/form_base->rect.w+i][hover_y+i].color = pen;

        }

        Render();
        SDL_SetWindowTitle(Editor::window,("PPM EDITOR 0.2.0 - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1] + " *").c_str());
        Editor::keys[SDLK_r] = false;

    }
    pas au point...
    */

    if (Editor::keys[SDLK_i] && enter) {

        if (!EqualColors(px->color,pen)) Editor::picker->SetColor(px->color);

        Editor::keys[SDLK_i] = false;

    }

    if (Editor::keys[SDLK_g] && enter) {

        Color base = px->color;
        std::vector<Pixel*> colored = {px};
        int posX(0),posY(0);

        do {

            posX = colored[0]->rect.x/colored[0]->rect.w;
            posY = colored[0]->rect.y/colored[0]->rect.h;

            if (posX < (int)pixels.size()-1 && posX > 0 && posY < (int)pixels[0].size()-1 && posY > 0) {
                
                if (EqualColors(pixels[posX+1][posY].color,base)) {

                    pixels[posX+1][posY].color = pen;
                    if (!VectorPixelHas(colored,&pixels[posX+1][posY])) colored.push_back(&pixels[posX+1][posY]);

                }

                if (EqualColors(pixels[posX-1][posY].color,base)) {

                    pixels[posX-1][posY].color = pen;
                    if (!VectorPixelHas(colored,&pixels[posX-1][posY])) colored.push_back(&pixels[posX-1][posY]);

                }

                if (EqualColors(pixels[posX][posY+1].color,base)) {

                    pixels[posX][posY+1].color = pen;
                    if (!VectorPixelHas(colored,&pixels[posX][posY+1])) colored.push_back(&pixels[posX][posY+1]);

                }

                if (EqualColors(pixels[posX][posY-1].color,base)) {

                    pixels[posX][posY-1].color = pen;
                    if (!VectorPixelHas(colored,&pixels[posX][posY-1])) colored.push_back(&pixels[posX][posY-1]);

                }

                if (posX == 1 && posY == 1 &&
                    pixels[0][0].color.red == base.red &&
                    pixels[0][0].color.green == base.green &&
                    pixels[0][0].color.blue == base.blue) pixels[0][0].color = pen;

                if (posX == (int)pixels.size()-2 && posY == 1 &&
                    pixels[pixels.size()-1][0].color.red == base.red &&
                    pixels[pixels.size()-1][0].color.green == base.green &&
                    pixels[pixels.size()-1][0].color.blue == base.blue) pixels[pixels.size()-1][0].color = pen;

                if (posX == 1 && posY == (int)pixels[0].size()-2 &&
                    pixels[0][pixels[0].size()-1].color.red == base.red &&
                    pixels[0][pixels[0].size()-1].color.green == base.green &&
                    pixels[0][pixels[0].size()-1].color.blue == base.blue) pixels[0][pixels[0].size()-1].color = pen;

                if (posX == (int)pixels.size()-2 && posY == (int)pixels[0].size()-2 &&
                    pixels[pixels.size()-1][pixels[0].size()-1].color.red == base.red &&
                    pixels[pixels.size()-1][pixels[0].size()-1].color.green == base.green &&
                    pixels[pixels.size()-1][pixels[0].size()-1].color.blue == base.blue) pixels[pixels.size()-1][pixels[0].size()-1].color = pen;

            }

            colored.erase(colored.begin(),colored.begin()+1);

        } while (colored.size() > 0);
        //à améliorer ...

        Render();
        SDL_SetWindowTitle(Editor::window,("PPM EDITOR 0.2.0 - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1] + " *").c_str());

        colored.clear();// je ne delete pas les pixels car ils appartiennent à la Class image du coup c'est dans le destructeur ;)

        Editor::keys[SDLK_g] = false;

    }

}

void Image::Load(std::string p) {

    path = p;

    if (ExistingFile(path)) {

        std::cout << "Reading File..." << std::endl;
        content = GetContentFile(path);
        std::cout << "Converting File..." << std::endl;
        pixels = Convert_StringToPixels(content);
        settings = Convert_StringToSettings(GetArrayLinesFile(path)[0]);
        Render();


    } else {

        

        for (int i = 0;i < settings.sizeX;i++) {

            pixels.push_back(*(new std::vector<Pixel>));

            for (int j = 0;j < settings.sizeY;j++) {

                //pixels[i].push_back(*(new Pixel(NULL,NULL,NULL)));
                pixels[i].push_back(*(new Pixel(/*rand()%256*/0,/*rand()%256*/0,/*rand()%256*/0)));

            }

        }

        content = Convert_SettingsToString(settings) + Convert_PixelsToString(pixels);
        Save();
        Render();

    }

    SDL_SetWindowTitle(Editor::window,("PPM EDITOR 0.0.1 - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1]).c_str());

}