#include "sceneManager.h"

bool SceneManager::StartUp() {
	current_scene_ = new Scene(current_scene_id_);

}

void SceneManager::SwitchScene() {

}

void SceneManager::ShutDown() {

}
  
void SceneManager::Update(const unsigned int deltaT) const {
	current_scene_->BuildSceneBounding();
	current_scene_->BuildGlobalOctree();
}