#include "gameObject.h"

void GameObject::BuildBounding() {
	bound_.BuildBound(mesh_ptr_->vertex_list_);
}

void GameObject::BuildLocalOctree() {

}