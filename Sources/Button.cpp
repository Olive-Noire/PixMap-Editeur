#include "../Headers/Button.hpp"

#include "../Headers/Editor.hpp"

void Button::Render() const {

    SDL_SetRenderDrawColor(Editor::renderer,color.red,color.green,color.blue,255);
    SDL_RenderFillRect(Editor::renderer,&rect);
    SDL_SetRenderDrawColor(Editor::renderer,0,0,0,255);

}

bool Button::Hover() const {

    return (rect.x + rect.w) >= Editor::mousePos[0] && (Editor::mousePos[0] + 1) >= rect.x && (rect.y + rect.h) >= Editor::mousePos[1] && (Editor::mousePos[1] + 1) >= rect.y;

}