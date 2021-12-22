#ifndef HITTABLE_H_
#define HITTABLE_H_
#include "mesh.h"
#include "bounding.h"

class Hittable {
public:
	//constructor
	Hittable(Mesh* _mesh_ptr,Bounding* _bound_ptr):mesh_ptr_(_mesh_ptr), bound_ptr_(_bound_ptr){}

	~Hittable()
	{
		delete bound_ptr_;
		delete mesh_ptr_;
		bound_ptr_ = nullptr;
		mesh_ptr_ = nullptr;
	}

	//data
	Bounding* bound_ptr_ = nullptr;
	Mesh* mesh_ptr_= nullptr;
};

#endif // !HITTABLE_H_
