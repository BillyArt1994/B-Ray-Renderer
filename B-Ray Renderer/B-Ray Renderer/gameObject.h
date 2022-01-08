#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "octree.h"
#include "transform.h"

class GameObject{
public:
	//constructor
	GameObject(Mesh* _mesh_ptr_):mesh_ptr_(_mesh_ptr_){}
	//destructor
	~GameObject() {
		delete bound_ptr_;
		bound_ptr_ = nullptr;
	}
	//funaction
	void BuildLocalOctree();

	template<typename T>
	void BuildBounds() {
		bound_ptr_ = new T(mesh_ptr_->vertex_list_);
	}

	//data
	Mesh* mesh_ptr_ = nullptr;
	Bounds* bound_ptr_ = nullptr;
	Transform transform_;
	TriangleOctree local_octree_;
};

#endif // !GAMEOBJECT_H_
