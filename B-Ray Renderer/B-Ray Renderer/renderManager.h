#ifndef RENDERMANAGER_H_
#define RENDERMANAGER_H_
#include "sceneManager.h"
#include "displayManager.h"
#include "render.h"

class RenderManager {
public:
	RenderManager() = default;

	bool StartUp(SceneManager& _sceneManager, DisplayManager& _displayManager);
	void ShutDown();
	void Render();

private:
	SceneManager* sceneManager_;
	DisplayManager* displayManager_;
};

#endif // !RENDERMANAGER_H_
