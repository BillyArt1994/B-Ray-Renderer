#ifndef HITTABLE_H_
#define HITTABLE_H_
#include "mesh.h"
#include "bounding.h"
#include "gameObject.h"
#include <vector>

class Hittable {
public:
	//constructor
	Hittable(Bounding* _bound_ptr_):bound_ptr_(_bound_ptr_){}

	virtual ~Hittable()
	{
		bound_ptr_ = nullptr;
	}

	//data
	Bounding* bound_ptr_ = nullptr;
};

class MeshHittable:public Hittable {
public:
	//constructor
	MeshHittable(GameObject* _obj_ptr_):obj_ptr_(_obj_ptr_), Hittable(&_obj_ptr_->bound_){}

	~MeshHittable()
	{
		obj_ptr_ = nullptr;
	}

	//data
	GameObject* obj_ptr_= nullptr;
};

class TriangleHittable :public Hittable {
public:
	//constructor
	TriangleHittable(Triangle* _triangle_ptr_) :triangle_ptr_(_triangle_ptr_), Hittable(&_triangle_ptr_->bound_) {}

	~TriangleHittable()
	{
		triangle_ptr_ = nullptr;
	}

	//data
	Triangle* triangle_ptr_ = nullptr;
};

#endif // !HITTABLE_H_
