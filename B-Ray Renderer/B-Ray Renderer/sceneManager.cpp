#include "sceneManager.h"

bool SceneManager::StartUp() {
	current_scene_ = new Scene(current_scene_id_);
	return false;
}

void SceneManager::SwitchScene(const unsigned id) {
	if (current_scene_!=nullptr&& current_scene_id_!= id)
	{
		delete current_scene_;
		current_scene_ = new Scene(id);
	}
	else
	{
		printf("场景加载失败已,此场景已加载.\n");
	}
}

void SceneManager::ShutDown() {
	delete current_scene_;
	current_scene_ = nullptr;
}
  
void SceneManager::Update(const unsigned int deltaT) const {
	current_scene_->Update(deltaT);
}