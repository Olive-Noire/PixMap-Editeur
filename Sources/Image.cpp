#include "../Headers/Image.hpp"

#include "../Headers/Convert.hpp"
#include "../Headers/Files.hpp"
#include "../Headers/Editor.hpp"
#include "../Headers/Types.hpp"

Image::Image(std::string p/*,Settings s*/) {

    Load(p);

}

Image::~Image() {}

void Image::Save() {

    const int &start(SDL_GetTicks());

    write.open(path);
    write << Convert_SettingsToString(settings) + Convert_PixelsArraysToString(pixels,settings.version);
    if (std::string(SDL_GetWindowTitle(Editor::window)).back() == '*') {
        
        std::string title(SDL_GetWindowTitle(Editor::window));
        title.pop_back();
        SDL_SetWindowTitle(Editor::window,title.c_str());

    }
    write.close();

    Editor::SavesPerfs.push_back(SDL_GetTicks()-start);

}

void Image::Render() const {

    const int &start(SDL_GetTicks());

    for (unsigned int i(0);i < pixels.size();i++) {

        for (unsigned int j(0);j < pixels[i].size();j++) {

            SDL_SetRenderDrawColor(Editor::renderer,pixels[i][j].red*(255/settings.maxColor),pixels[i][j].green*(255/settings.maxColor),pixels[i][j].blue*(255/settings.maxColor),255);
            const SDL_Rect &pixel{(int)i*PixelWidth,(int)j*PixelHeight,PixelWidth,PixelHeight};
            SDL_RenderFillRect(Editor::renderer,&pixel);

        }

    }

    SDL_SetRenderDrawColor(Editor::renderer,0,0,0,0);
    SDL_RenderPresent(Editor::renderer);

    Editor::rendersPerfs.push_back(SDL_GetTicks()-start);

}

void Image::Update() {

    if (settings.version == Version::P1) pen = Color(1,1,1); else pen = Editor::picker->GetColor();

    const unsigned int &id = SDL_GetWindowID(Editor::window);
    const bool &enter(id == Editor::event.window.windowID);

    Color& px = pixels[Editor::mousePos[0]/PixelWidth][Editor::mousePos[1]/PixelHeight];

    //if (Editor::keys[SDLK_LSHIFT] && enter) form_base = px;

    if (Editor::keys[SDLK_LCTRL] && Editor::keys[SDLK_s]) {

        Save();
        Editor::keys[SDLK_LCTRL] = false;
    
    }

    if (Editor::mouses[SDL_BUTTON_LEFT] && enter) {

        if (px != pen) {

            px = pen;
            Render();
            if (std::string(SDL_GetWindowTitle(Editor::window)).back() != '*') SDL_SetWindowTitle(Editor::window,std::string(std::string(SDL_GetWindowTitle(Editor::window))+"*").c_str());

        }

    }

    if (Editor::mouses[SDL_BUTTON_RIGHT] && enter) {

        if (px != Color()) {

            px = Color();
            Render();
            if (std::string(SDL_GetWindowTitle(Editor::window)).back() != '*') SDL_SetWindowTitle(Editor::window,std::string(std::string(SDL_GetWindowTitle(Editor::window))+"*").c_str());

        }

    }

    /*if (Editor::keys[SDLK_v]) {

        std::cout << Convert_SettingsToString(settings) + Convert_PixelsArraysToString(pixels,settings.version) << std::endl;

        Editor::keys[SDLK_v] = false;

    }*/

    if (Editor::keys[SDLK_c]) {

        for (unsigned int i(0);i < pixels.size();i++) {

            for (unsigned int j(0);j < pixels[i].size();j++) {

                if (pixels[i][j] != Color()) pixels[i][j] = Color();

            }

        }

        Render();
        if (std::string(SDL_GetWindowTitle(Editor::window)).back() != '*') SDL_SetWindowTitle(Editor::window,std::string(std::string(SDL_GetWindowTitle(Editor::window))+"*").c_str());

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
        if (std::string(SDL_GetWindowTitle(Editor::window)).back() != '*') SDL_SetWindowTitle(Editor::window,std::string(std::string(SDL_GetWindowTitle(Editor::window))+"*").c_str());
        Editor::keys[SDLK_r] = false;

    }
    pas au point...
    */

    if (Editor::keys[SDLK_i] && enter) {

        if (px != pen) Editor::picker->SetColor(px);

        Editor::keys[SDLK_i] = false;

    }

    if (Editor::keys[SDLK_g] && enter) {

        const Color &base = px;
        if (base != pen) {

            std::vector<Color> colored = {px};
            int posX(0),posY(0);

            do {

                //posX = colored[0].position.x/PixelWidth;
                //posY = colored[0].position.y/PixelHeight;
                colored[0] = pen;

                if (posX == 0 && posY == 0) {

                    if (pixels[posX+1][posY] == base && !VectorColorHas(colored,pixels[posX+1][posY])) colored.push_back(pixels[posX+1][posY]);
                    if (pixels[posX][posY+1] == base && !VectorColorHas(colored,pixels[posX][posY+1])) colored.push_back(pixels[posX][posY+1]);

                }

                if (posX == 0 && posY == (int)pixels[posX].size() - 1) {

                    if (pixels[posX+1][posY] == base && !VectorColorHas(colored,pixels[posX+1][posY])) colored.push_back(pixels[posX+1][posY]);
                    if (pixels[posX][posY-1] == base && !VectorColorHas(colored,pixels[posX][posY-1])) colored.push_back(pixels[posX][posY-1]);

                }

                if (posX == (int)pixels.size() - 1 && posY == 0) {

                    if (pixels[posX-1][posY] == base && !VectorColorHas(colored,pixels[posX-1][posY])) colored.push_back(pixels[posX-1][posY]);
                    if (pixels[posX][posY+1] == base && !VectorColorHas(colored,pixels[posX][posY+1])) colored.push_back(pixels[posX][posY+1]);

                }
            
                if (posX == (int)pixels.size() - 1 && posY == (int)pixels[0].size() - 1) {

                    if (pixels[posX-1][posY] == base && !VectorColorHas(colored,pixels[posX-1][posY])) colored.push_back(pixels[posX-1][posY]);
                    if (pixels[posX][posY-1] == base && !VectorColorHas(colored,pixels[posX][posY-1])) colored.push_back(pixels[posX][posY-1]);

                }
            
                if (posX == 0 && posY > 0 && posY < (int)pixels[0].size() - 1) {

                    if (pixels[posX+1][posY] == base && !VectorColorHas(colored,pixels[posX+1][posY])) colored.push_back(pixels[posX+1][posY]);
                    if (pixels[posX][posY+1] == base && !VectorColorHas(colored,pixels[posX][posY+1])) colored.push_back(pixels[posX][posY+1]);
                    if (pixels[posX][posY-1] == base && !VectorColorHas(colored,pixels[posX][posY-1])) colored.push_back(pixels[posX][posY-1]);

                }
            
                if (posX == (int)pixels.size() - 1 && posY > 0 && posY < (int)pixels[0].size() - 1) {

                    if (pixels[posX-1][posY] == base && !VectorColorHas(colored,pixels[posX-1][posY])) colored.push_back(pixels[posX-1][posY]);
                    if (pixels[posX][posY+1] == base && !VectorColorHas(colored,pixels[posX][posY+1])) colored.push_back(pixels[posX][posY+1]);
                    if (pixels[posX][posY-1] == base && !VectorColorHas(colored,pixels[posX][posY-1])) colored.push_back(pixels[posX][posY-1]);

                }
            
                if (posY == 0 && posX > 0 && posY < (int)pixels.size() - 1) {

                    if (pixels[posX][posY+1] == base && !VectorColorHas(colored,pixels[posX][posY+1])) colored.push_back(pixels[posX][posY+1]);
                    if (pixels[posX+1][posY] == base && !VectorColorHas(colored,pixels[posX+1][posY])) colored.push_back(pixels[posX+1][posY]);
                    if (pixels[posX-1][posY] == base && !VectorColorHas(colored,pixels[posX-1][posY])) colored.push_back(pixels[posX-1][posY]);

                }
            
                if (posY == (int)pixels[0].size() - 1 && posX > 0 && posX < (int)pixels.size() - 1) {

                    if (pixels[posX][posY-1] == base && !VectorColorHas(colored,pixels[posX][posY-1])) colored.push_back(pixels[posX][posY-1]);
                    if (pixels[posX+1][posY] == base && !VectorColorHas(colored,pixels[posX+1][posY])) colored.push_back(pixels[posX+1][posY]);
                    if (pixels[posX-1][posY] == base && !VectorColorHas(colored,pixels[posX-1][posY])) colored.push_back(pixels[posX-1][posY]);

                }

                if (posX > 0 && posY > 0 && posX < (int)pixels.size() - 1 && posY < (int)pixels[0].size() - 1) {

                    if (pixels[posX+1][posY] == base && !VectorColorHas(colored,pixels[posX+1][posY])) colored.push_back(pixels[posX+1][posY]);
                    if (pixels[posX][posY+1] == base && !VectorColorHas(colored,pixels[posX][posY+1])) colored.push_back(pixels[posX][posY+1]);
                    if (pixels[posX-1][posY] == base && !VectorColorHas(colored,pixels[posX-1][posY])) colored.push_back(pixels[posX-1][posY]);
                    if (pixels[posX][posY-1] == base && !VectorColorHas(colored,pixels[posX][posY-1])) colored.push_back(pixels[posX][posY-1]);

                }

                //std::find(pixels.begin(),pixels.end(),base);
            
                colored.erase(colored.begin(),colored.begin()+1);

            } while (colored.size() > 0);
        
        
            colored.clear();// je ne delete pas les pixels car ils appartiennent à la Class image du coup c'est dans le destructeur ;)

            Render();
            if (std::string(SDL_GetWindowTitle(Editor::window)).back() != '*') SDL_SetWindowTitle(Editor::window,std::string(std::string(SDL_GetWindowTitle(Editor::window))+"*").c_str());

        }

        Editor::keys[SDLK_g] = false;

    }

}

void Image::Load(const std::string &p) {

    const int &start(SDL_GetTicks());

    if (!pixels.empty()) pixels.clear();

    if (ExistingFile(p)) {

        settings = Convert_StringToSettings(GetArrayLinesFile(p)[0]);

        if (settings.version != Version::P1) {

            Editor::picker = new Picker();
            Editor::picker->SetColorMod(settings.version == Version::P3);
            Editor::picker->Render();

        }

        pixels = Convert_StringToPixelsArrays(GetContentFile(p),settings.version);


    } else {

        if (settings.version != Version::P1) {

            Editor::picker = new Picker();
            Editor::picker->SetColorMod(settings.version == Version::P3);
            Editor::picker->Render();

        }

        pixels = std::vector<std::vector<Color>>(settings.sizeX,std::vector<Color>(settings.sizeY,Color()));
        Save();

    }

    path = p;

    int width,height;
    SDL_GetRendererOutputSize(Editor::renderer,&width,&height);

    PixelWidth = (int)width/pixels.size();
    PixelHeight = (int)height/pixels[0].size();

    Render();

    SDL_SetWindowTitle(Editor::window,("PPM EDITOR " + Editor::version + " - " + Split(Split(path,'\\')[Split(path,'\\').size()-1],'/')[Split(Split(path,'\\')[Split(path,'\\').size()-1],'/').size()-1]).c_str());

    Editor::LoadsPerfs.push_back(SDL_GetTicks()-start);

}