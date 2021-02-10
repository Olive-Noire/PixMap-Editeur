#include "../../Headers/Class/Image.hpp"

#include <iostream>

#include "../../Headers/Functions/Convert.hpp"
#include "../../Headers/Functions/Files.hpp"

#include "../../Headers/Class/Editor.hpp"

Image::Image(std::string p,Settings s) {

    path = p;
    settings = s;

    if (ExistingFile(path)) {

        std::cout << "Reading File..." << std::endl;
        content = GetContentFile(path);
        //std::cout << "finish !" << std::endl;
        //std::cin.ignore();
        //std::system("cls");
        std::cout << "Converting File..." << std::endl;
        pixels = Convert_StringToPixels(content);
        settings = Convert_StringToSettings(GetArrayLinesFile(path)[0]);
        //std::cout << std::endl << "finish !" << std::endl;
        //std::cin.ignore();
        //std::system("cls");


    } else {

        for (int i = 0;i < settings.sizeX;i++) {

            pixels.push_back(*(new std::vector<Pixel>));

            for (int j = 0;j < settings.sizeY;j++) {

                //pixels[i].push_back(*(new Pixel(NULL,NULL,NULL)));
                pixels[i].push_back(*(new Pixel(/*rand()%256*/NULL,/*rand()%256*/NULL,/*rand()%256*/NULL)));

            }

        }

        content = Convert_SettingsToString(settings) + Convert_PixelsToString(pixels);
        Save();

    }

}

Image::~Image() {

    write.close();
    read.close();

}

void Image::Save() {

    write.open(path);
    write << content;
    write.close();
    SDL_SetWindowTitle(Editor::window,"PPM EDITOR 0.0.1");

}

void Image::Render() {

    /*
    std::cout << "launch rendering : " << std::endl;
    std::cin.ignore();

    std::cout << "h: " << pixels.size() << " w: " << pixels[0].size() << std::endl;

    for (int i = 0;i < pixels.size();i++) {

        for (int j = 0;j < pixels[i].size();j++) {

            std::cout << i << "/" << j << " : " << "r:" << pixels[i][j].color.red << "/g:" << pixels[i][j].color.green << "/b:" << pixels[i][j].color.blue << std::endl;

        }

    }

    */

    int width,height;
    SDL_GetRendererOutputSize(Editor::renderer,&width,&height);

    int PixelWidth(width/pixels.size()),PixelHeight(height/pixels[0].size());

    for (int i = 0;i < pixels.size();i++) {

        for (int j = 0;j < pixels[i].size();j++) {

            pixels[i][j].rect = {i*PixelWidth,j*PixelHeight,PixelWidth,PixelHeight};

            SDL_SetRenderDrawColor(Editor::renderer,pixels[i][j].color.red,pixels[i][j].color.green,pixels[i][j].color.blue,255);
            SDL_RenderFillRect(Editor::renderer,&pixels[i][j].rect);

        }

    }

    SDL_SetRenderDrawColor(Editor::renderer,0,0,0,0);
    SDL_RenderPresent(Editor::renderer);

}

void Image::Update() {

    Pixel* px = &pixels[(Editor::mousePos[0] / pixels[0][0].rect.w)][(Editor::mousePos[1] / pixels[0][0].rect.h)];

    if (Editor::keys[SDLK_LCTRL] && Editor::keys[SDLK_s]) {
        
        content = Convert_SettingsToString(settings) + Convert_PixelsToString(pixels);
        pixels = Convert_StringToPixels(content);
        Save();
        Render();

        Editor::keys[SDLK_LCTRL] = false;
    
    }

    if (Editor::mouses[SDL_BUTTON_LEFT]) {

        px->color = pen;
        Render();
        SDL_SetWindowTitle(Editor::window,"PPM EDITOR 0.0.1 *");

    }

    if (Editor::mouses[SDL_BUTTON_RIGHT]) {

        px->color.red = px->color.green = px->color.blue = 0;
        Render();
        SDL_SetWindowTitle(Editor::window,"PPM EDITOR 0.0.1 *");

    }

    if (Editor::keys[SDLK_c]) {

        std::system("cls");

        std::string r_s,g_s,b_s;

        std::cout << "red : ";
        std::getline(std::cin,r_s);
        std::cout << "green : ";
        std::getline(std::cin,g_s);
        std::cout << "blue : ";
        std::getline(std::cin,b_s);

        pen = {Convert_StringToNumber(r_s),Convert_StringToNumber(g_s),Convert_StringToNumber(b_s)};

        Editor::keys[SDLK_c] = false;

    }

    if (Editor::keys[SDLK_v]) {

        std::system("cls");

        std::cout << content;

        Editor::keys[SDLK_v] = false;

    }

    if (Editor::keys[SDLK_d]) {

        for (int i = 0;i < pixels.size();i++) {

            for (int j = 0;j < pixels[i].size();j++) {

                pixels[i][j].color.red = pixels[i][j].color.green = pixels[i][j].color.blue = 0;

            }

        }

        Render();
        SDL_SetWindowTitle(Editor::window,"PPM EDITOR 0.0.1 *");

    }

}

void Image::Load(std::string path) {



}