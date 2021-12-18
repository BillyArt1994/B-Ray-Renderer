#ifndef ENGINE_H_
#define ENGINE_H_
#include "displayManager.h"
#include "sceneManager.h"
#include "inputManager.h"
#include "renderManager.h"

class Engine {
public:
	//constructor
	Engine() = default;
	//funaction
	bool StartUp();
	void ShutDown();
	void Run();
private:
	//data
	DisplayManager displayManager_;
	SceneManager sceneManager_;
	InputManager inputManager_;
	RenderManager renderManager_;
};

#endif // !ENGINE_H_
