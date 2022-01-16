#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "transform.h"
#include "bounding.h"
#include "mesh.h"

class Octree;

class GameObject{
public:
	//constructor
	GameObject(Mesh _mesh):mesh_(_mesh){}

	//destructor
	~GameObject() {
		delete bound_ptr_;
		bound_ptr_ = nullptr;
	}

	//funaction
	void BuildLocalOctree();

	template<typename T>
	void BuildBounds() {
		bound_ptr_ = new T(mesh_);
	}

	//data
	Mesh mesh_;
	Bounds* bound_ptr_ = nullptr;
	Transform transform_;
	Octree local_octree_;
};

#endif // !GAMEOBJECT_H_
