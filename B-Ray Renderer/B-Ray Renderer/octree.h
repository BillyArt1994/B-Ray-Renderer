#ifndef  OCTREE_H_
#define  OCTREE_H_

#include "bounding.h"
#include <vector>
#include "mesh.h"
#include "gameObject.h"

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
		node(const std::vector<unsigned>& _data,const BoxBounding& _bound,const bool _is_leaf) :data(_data), boxbound(_bound), is_leaf(_is_leaf) {}
		node(const BoxBounding& _bound, const bool& _is_leaf) :boxbound(_bound), is_leaf(_is_leaf) {}
		//funaction
	public:
		void recursiveDestory(node* node);
		//destructor
		~node() {
			recursiveDestory(this);
		}
		//data
		std::vector<unsigned> data{0u};
		BoxBounding boxbound;
		node* sub_node[8]{nullptr};
		bool is_leaf = false;
	};

	//funaction
	void OctreeBuild(node* node_ptr, std::vector<GameObject>* gameObject_array_ptr,const std::vector<unsigned>& index_array, const BoxBounding& bound, const unsigned depth);

	node* LookUpNode(const Vec3& pos);

public:
	Octree() = default;

	void BuildTree(std::vector<GameObject>* _gameObject_list_ptr, const BoxBounding& bound);

	//八叉树光线求交
	bool Intersect(const Ray& r);

	node* root_node_ptr_ = nullptr;

	unsigned maxcount = 0u;
};

#endif // ! OCTREE_H_
