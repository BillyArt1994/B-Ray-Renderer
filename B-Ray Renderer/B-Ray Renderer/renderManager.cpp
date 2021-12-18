#include "renderManager.h"

bool RenderManager::StartUp(SceneManager& _sceneManager, DisplayManager& _displayManager)
{
	sceneManager_ = &_sceneManager;
	displayManager_ = &_displayManager;
	return true;
}

void RenderManager::Render() {

}