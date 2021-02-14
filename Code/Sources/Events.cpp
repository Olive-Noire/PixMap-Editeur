#include "../Headers/Events.hpp"

#include <SDL.h>
#include <iostream>

#include "../Headers/Editor.hpp"

void UpdateKeys(SDL_Event event) {

    switch (event.type) {

		case SDL_KEYDOWN:
		Editor::keys[event.key.keysym.sym] = true;
		break;

		case SDL_KEYUP:
		Editor::keys[event.key.keysym.sym] = false;
		break;

		default:
		break;

	}

}

void UpdateMouse(SDL_Event event) {

    //if (event.type != SDL_MOUSEBUTTONDOWN) std::cout << "not mouse" << std::endl;

    switch(event.type) {

        case SDL_MOUSEBUTTONDOWN:
        //std::cout << "mouse down" << std::endl;
        if (!Editor::mouses[event.button.button]) Editor::mouses[event.button.button] = true;
        break;

        case SDL_MOUSEBUTTONUP:
        Editor::mouses[event.button.button] = false;
        break;

        case SDL_MOUSEMOTION:
        Editor::mousePos[0] = event.motion.x;
        Editor::mousePos[1] = event.motion.y;
        Editor::mousePos[2] = event.motion.xrel;
        Editor::mousePos[3] = event.motion.yrel;
        break;

        case SDL_MOUSEWHEEL:
        Editor::wheel = event.wheel.y;
        break;

        default:
        //Game::mousePos[2] = 0;
        //Game::mousePos[3] = 0;
        //Game::wheel = 0;
        break;

    }

    if (event.type != SDL_MOUSEMOTION) {

        Editor::mousePos[2] = 0;
        Editor::mousePos[3] = 0;

    }

    if (event.type != SDL_MOUSEWHEEL) Editor::wheel = 0;

}