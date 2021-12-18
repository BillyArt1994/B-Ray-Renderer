#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include "libary/SDL/include/SDL.h"

class InputManager {
public:
	bool StartUp();
	void ShutDown();
	void ProcessInput(bool& _done);
public:
	void HandleEvent(SDL_Event* event, bool& done);
};

#endif // !INPUTMANAGER_H_
