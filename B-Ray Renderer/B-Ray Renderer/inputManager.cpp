#include "inputManager.h"

bool InputManager::StartUp() {
	bool success = !SDL_SetRelativeMouseMode(SDL_TRUE);
    return success;
}

void InputManager::ShutDown() {

}

void InputManager::ProcessInput(bool& _done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _done = true;
            return;
        }
        else {
            HandleEvent(&event, _done);
        }
    }
}

void InputManager::HandleEvent(SDL_Event* event, bool& done) {

}