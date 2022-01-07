#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "octree.h"
#include "transform.h"
#include "triangle.h"

class GameObject{
public:
	//constructor
	GameObject(Mesh* _mesh_ptr_):mesh_ptr_(_mesh_ptr_){}
	//funaction
	void BuildLocalOctree();
	void BuildBounding();
	//data
	Mesh* mesh_ptr_ = nullptr;
	BoxBounding bound_;
	Transform transform_;
	TriangleOctree local_octree_;
};

#endif // !GAMEOBJECT_H_
