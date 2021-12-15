#ifndef HITTABLE_H_
#define HITTABLE_H_
#include "mesh.h"
#include "octree.h"
#include "bounding.h"

class Hittable {
public:
	//constructor
	Hittable(const Mesh* _mesh_ptr):mesh_ptr_(_mesh_ptr){}
	//funaction
	bool BoundOctree();
	bool BulidBounding();
	//data
	BoxBounding bound_;
	const Mesh* mesh_ptr_= nullptr; 
	Octree<Triangle> octree_root_;
};

#endif // !HITTABLE_H_
