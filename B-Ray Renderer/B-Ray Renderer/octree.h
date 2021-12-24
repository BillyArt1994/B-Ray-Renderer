#ifndef  OCTREE_H_
#define OCTREE_H_
#include "bounding.h"
#include "hittable.h"
#include <vector>

/*
    x  y  z
 0  0  0  0
 1  1  0  0
 2  0  1  0
 3  1  0  1
 4  0  0  1
 5  1  0  1
 6  0  1  1
 7  1  1  1
*/

class Octree {
private:
	//八叉树节点数据
	struct node {
		//constructor
		node() = default;
		node(const std::vector<Hittable*>& _data,const BoxBounding& _bound,const bool _is_leaf) :data(_data), boxbound(_bound), is_leaf(_is_leaf) {}
		node(const BoxBounding& _bound, const bool& _is_leaf) :boxbound(_bound), is_leaf(_is_leaf) {}
		//funaction
	public:
		void recursiveDestory(node* node);
		//destructor
		~node() {
			recursiveDestory(this);
		}
		//data
		std::vector<Hittable*> data{nullptr};
		BoxBounding boxbound;
		node* sub_node[8]{ nullptr };
		bool is_leaf = false;
	};

	node* OctreeBuild(const std::vector<Hittable*>& data_ptr, const BoxBounding& bound, const unsigned depth);

	//八叉树节点查找
	node* LookUpNode(const Vec3& pos);
public:
	Octree() = default;

	void BuildTree(const std::vector<Hittable*>& data_ptr, const BoxBounding& bound, const unsigned depth);

	//八叉树光线求交
	bool Intersect(const Ray& r);

	node* root_node_ptr_ = nullptr;

};

#endif // ! OCTREE_H_
