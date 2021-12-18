#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include "scene.h"


class SceneManager {
public:
	//constructor
	SceneManager() = default;
	//funaction
	bool StartUp();
	void ShutDown();
	void Update(unsigned int deltaT);
	void SwitchScene();

	Scene* get_current_scene_() const{return current_scene_;}
private:
	//data
	unsigned current_scene_id_ = 1u;
	Scene* current_scene_ = nullptr;
};
#endif // !SCENEMANAGER_H_
