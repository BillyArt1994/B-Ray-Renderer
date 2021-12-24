#include "gameObject.h"

void GameObject::BuildBounding() {
	bound_.BuildBound(mesh_ptr_->vertex_list_);
}

void GameObject::BuildOctree() {
	std::vector<Hittable*> tri_hittable_array;
	const unsigned length = mesh_ptr_->get_face_count_();
	for (size_t i = 0; i < length; i++)
	{
		mesh_ptr_->triangle_list_[i].bound_.BuildBound(mesh_ptr_->vertex_list_);
		TriangleHittable a(&(mesh_ptr_->triangle_list_[i]));
		tri_hittable_array.push_back(&a);
	}
	local_octree_.BuildTree(tri_hittable_array,bound_,32);
}