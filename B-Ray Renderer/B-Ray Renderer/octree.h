#ifndef  OCTREE_H_
#define OCTREE_H_
#include "bounding.h"
#include "hittable.h"
#include <vector>

class Octree {
private:
	struct node {
		//constructor
		node() = default;
		node(const std::vector<Hittable>& _data,const BoxBounding& _bound,const bool _is_leaf) :data(_data), boxbound(_bound), is_leaf(_is_leaf) {}
		node(const BoxBounding& _bound, const bool& _is_leaf) :boxbound(_bound), is_leaf(_is_leaf) {}
		//funaction
	public:
		void recursiveDestory(node* node);
		//destructor function
		~node() {
			recursiveDestory(this);
		}
		//data
		std::vector<Hittable> data;
		BoxBounding boxbound;
		node* sub_node[8]{ nullptr };
		bool is_leaf = false;
	};

	node* OctreeBuild(const std::vector<Hittable>& data_ptr, const BoxBounding& bound, const unsigned depth);

public:
	Octree() = default;

	void BuildTree(const std::vector<Hittable>& data_ptr, const BoxBounding& bound, const unsigned depth);

	bool Intersect(const Ray& r);

	node* root_node_ptr_ = nullptr;
};

#endif // ! OCTREE_H_
