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
	Scene(unsigned _id);
	//funaction
	void Update(unsigned int _deltaT);
	void LoadScene(unsigned _id);
	//data
	Camera* maincamera_;
	Light* light_;
	std::vector<Hittable> hittable_list_;
	Octree scene_octree;
	void BuildSceneBounding();
	void BuildGlobalOctree();
private:
	void BuildBounding();
	void BuildLocalOctree();
	//data
	BoxBounding scene_bound_;
};

#endif // !SCENE_H_
