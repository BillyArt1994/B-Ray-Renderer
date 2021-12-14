#ifndef HITTABLE_H_
#define HITTABLE_H_
#include "mesh.h"
#include "octree.h"

class Hittable {
	//constructor
	Hittable(const Mesh* _mesh):mesh_(_mesh){}
	//data
	const Mesh* mesh_= nullptr; 
	Octree<Triangle> octree_root_;
	//bool TriangleIntersect(const Ray& ray, float& t) {
	//	const Vec3 E1(mesh_ ->vertarray[idx2_].position - mesh_->vertarray[idx1_].position),
	//		E2(mesh_->vertarray[idx3_].position - mesh_->vertarray[idx1_].position),
	//		dir(ray.get_direction_()),
	//		P = Cross(dir, E2),
	//		T = dir - mesh_->vertarray[idx1_].position;
	//	const float det = Dot(E1, P), inv_det(1.0f / det),
	//		u = Dot(T, P) * inv_det;
	//	if (u < 0.0f || u>1.0f) return false;
	//	const Vec3 Q = Cross(T, E1);
	//	const float v = Dot(dir, Q) * inv_det;
	//	if (v < 0.0f || v + u>1.0f) return false;
	//	t = Dot(E2, Q) * inv_det;
	//	return true;
	//}
};

#endif // !HITTABLE_H_
