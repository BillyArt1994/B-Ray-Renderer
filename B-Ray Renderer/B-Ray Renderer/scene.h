#ifndef SCENE_H_
#define SCENE_H_
#include "camera.h"
#include "octree.h"
#include "light.h"
#include "hittable.h"
#include "bounding.h"
#include <vector>

class Scene {
public:
	//constructor
	explicit Scene(unsigned _id);
	//funaction
	void Update(unsigned int _deltaT);
	void StartUp();
	//data
	Camera* maincamera_ =nullptr;
	Light* light_ =nullptr;
	std::vector<GameObject> hittable_list_;
	Octree scene_octree;
	void BuildSceneBounding();
	void BuildGlobalOctree();
private:
	//funaction
	void LoadScene(unsigned _id);
	void BuildObjBounding();
	void BuildLocalOctree();
	//data
	BoxBounding scene_bound_;
};

#endif // !SCENE_H_
