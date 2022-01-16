#include "scene.h"

Scene::Scene(unsigned _id) {
	LoadScene(_id);
}

void Scene::LoadScene(unsigned _id) {
	switch (_id)
	{
	case 1:
		//hittable_list_.push_back(GameObject(Mesh("../scenes/scene_01/Torus.obj")));
		gameObject_array_.push_back(GameObject(Mesh("../scenes/scene_01/Torus.obj")));
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void Scene::StartUp() {
	BuildObjBounding();
	BuildLocalOctree();
	BuildSceneBounding();
	BuildGlobalOctree();
}

void Scene::Update(unsigned int _deltaT) {

}

void Scene::BuildObjBounding() {
	const size_t length = gameObject_array_.size();
	for (size_t i = 0; i < length; i++)
	{
		gameObject_array_[i].BuildBounds<BoxBounding>();
	}
}

void Scene::BuildLocalOctree() {
	const size_t length = gameObject_array_.size();
	for (size_t i = 0; i < length; i++)
	{
		gameObject_array_[i].BuildLocalOctree();
	}
}

void Scene::BuildSceneBounding() {
	size_t length = gameObject_array_.size();
	float x(0), y(0), z(0);
	Vec3 minpoint;
	Vec3 maxpoint;
	for (size_t i = 0; i < length; i++)
	{
		maxpoint = ((BoxBounding*)(gameObject_array_[i].bound_ptr_))->maxpoint_;
		minpoint = ((BoxBounding*)(gameObject_array_[i].bound_ptr_))->minpoint_;
		x = Max(Max(Abs(maxpoint.x), Abs(minpoint.x)), x);
		y = Max(Max(Abs(maxpoint.y), Abs(minpoint.y)), y);
		z = Max(Max(Abs(maxpoint.z), Abs(minpoint.z)), z);
	}
	const float boundlength = Nearest2Power(Max(x, y, z));
	scene_bound_ = BoxBounding(Vec3(-boundlength), Vec3(boundlength));
}

void Scene::BuildGlobalOctree() {
	//scene_octree.BuildTree(hittable_list_, scene_bound_, 32u);
}