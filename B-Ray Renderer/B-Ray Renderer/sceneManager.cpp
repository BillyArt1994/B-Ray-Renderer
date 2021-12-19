#include "sceneManager.h"

bool SceneManager::StartUp() {
#if 1
	current_scene_ = new Scene(current_scene_id_);
#endif // 0

}

void SceneManager::SwitchScene() {

}

void SceneManager::ShutDown() {

}
  
void SceneManager::Update(const unsigned int deltaT) const {
	
}