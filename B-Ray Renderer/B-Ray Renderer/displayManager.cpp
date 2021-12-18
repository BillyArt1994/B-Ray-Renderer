#include "displayManager.h"

bool DisplayManager::StartUp() {
	bool flag = true;
	if (!StartSDL())
	{
		flag = false;
	}
	else if (!CreateWindow())
	{
		flag = false;
	}
	else if (!CreateScreenSurface())
	{
		flag = false;
	}
	return true;
}

bool DisplayManager::StartSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL组件初始化失败: %s\n", SDL_GetError());
		return  false;
	}
	return true;
}

bool DisplayManager::CreateScreenSurface() {
	sdl_surface_ = SDL_GetWindowSurface(sdl_window_);
	if (sdl_surface_ == nullptr)
	{
		printf("无法获得屏幕表面 Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool DisplayManager::CreateWindow() {

	sdl_window_ = SDL_CreateWindow("B-ray Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (sdl_window_ == nullptr) {
		printf("窗口创建失败: %s\n", SDL_GetError());
		return false;
	}
	sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, 0);
	return true;
}

void DisplayManager::UpdateBuffer(unsigned char* buffer) {
	SDL_LockSurface(sdl_surface_);
	const int path = SCREEN_WIDTH * SCREEN_WIDTH * 3;
	memcpy(sdl_surface_->pixels, buffer, path);
	SDL_UnlockSurface(sdl_surface_);
	SDL_UpdateWindowSurface(sdl_window_);
	
}