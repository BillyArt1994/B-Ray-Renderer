#ifndef HITTABLE_H_
#define HITTABLE_H_
#include "mesh.h"
#include "bounding.h"

class Hittable {
public:
	//constructor
	Hittable(const Mesh* _mesh_ptr):mesh_ptr_(_mesh_ptr){}
	//funaction
	// 
	//data
	Bounding bound_;
	const Mesh* mesh_ptr_= nullptr; 
};

#endif // !HITTABLE_H_
