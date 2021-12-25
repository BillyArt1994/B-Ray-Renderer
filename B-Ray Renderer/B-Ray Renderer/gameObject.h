#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "octree.h"
#include "transform.h"
#include "triangle.h"

class GameObject{
public:
	//constructor
	GameObject(Mesh* _mesh_ptr_):mesh_ptr_(_mesh_ptr_){}
	GameObject(const Mesh& _mesh) {
		mesh_ptr_ = new Mesh(_mesh);
	}
	//funaction
	void BuildOctree();
	void BuildBounding();
	//data
	Mesh* mesh_ptr_ = nullptr;
	BoxBounding bound_;
	Transform transform_;
	Octree local_octree_;
};

#endif // !GAMEOBJECT_H_
