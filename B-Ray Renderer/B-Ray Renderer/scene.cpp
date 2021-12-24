#include "scene.h"

void LoadScene(unsigned _id) {
	//switch (_id)
	//{
	//case 1:
	//	Mesh box_big("./scene/simple_Scene_01/Big_Box.obj");
	//	Mesh box_small("./scene/simple_Scene_01/Box_Small.obj");
	//	Mesh ground("./scene/simple_Scene_01/Ground.obj");
	//	Mesh sphere("./scene/simple_Scene_01/Ground.obj");
	//	Mesh wall_left("./scene/simple_Scene_01/Wall_Left.obj");
	//	Mesh wall_right("./scene/simple_Scene_01/Wall_Right.obj");
	//	break;
	//case 2:

	//	break;
	//case 3:

	//	break;
	}

void Scene::Update(unsigned int _deltaT) {

}

void Scene::BuildBounding() {
	const size_t length = hittable_list_.size();
	for (size_t i = 0; i < length; i++)
	{
		hittable_list_[i].BuildBounding();
	}
}

void Scene::BuildLocalOctree() {
	const size_t length = hittable_list_.size();
	for (size_t i = 0; i < length; i++)
	{
		hittable_list_[i].BuildOctree();
	}
}

void Scene::BuildSceneBounding() {
	size_t length = hittable_list_.size();
	float x(0), y(0), z(0);
	Vec3 minpoint;
	Vec3 maxpoint;
	for (size_t i = 0; i < length; i++)
	{
		maxpoint = hittable_list_[i].bound_.maxpoint_;
		minpoint = hittable_list_[i].bound_.maxpoint_;
		x = Max(Max(Abs(maxpoint.x), Abs(minpoint.x)), x);
		y = Max(Max(Abs(maxpoint.y), Abs(minpoint.y)), y);
		z = Max(Max(Abs(maxpoint.z), Abs(minpoint.z)), z);
	}
	const float length = Max(x, y, z);
	scene_bound_ = BoxBounding(Vec3(-length), Vec3(length));
}

void Scene::BuildGlobalOctree() {
	scene_octree.BuildTree(hittable_list_, scene_bound_, 32u);
}