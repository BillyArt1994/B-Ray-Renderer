#ifndef DISPLAYMANAGER_H_
#define DISPLAYMANAGER_H_
#include <iostream>
#include "libary/SDL/include/SDL.h"

class DisplayManager {
public:
	//constructor
	DisplayManager() = default;
	//data
	constexpr static int SCREEN_WIDTH = 1280; //640 1280
	constexpr static int SCREEN_HEIGHT = 720; //480 720
	constexpr static float SCREEN_ASPECT_RATIO = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	//funaction
	bool StartUp();
	bool ShutDown();

	void UpdateBuffer(unsigned char* buffer);
private:
	bool StartSDL();
	bool CreateWindow();
	bool CreateScreenSurface();

	SDL_Window* sdl_window_ =nullptr;
	SDL_Renderer* sdl_renderer_ = nullptr;
	SDL_Surface* sdl_surface_ = nullptr;
};

#endif // !DISPLAYMANAGER_H_