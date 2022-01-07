#ifndef  OCTREE_H_
#define  OCTREE_H_
#include "bounding.h"
#include "gameObject.h"
#include <vector>
#include "mesh.h"

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


class ObjctOctree {
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
		node* sub_node[8]{ nullptr };
		bool is_leaf = false;
	};


	//funaction
	node* OctreeBuild(const std::vector<unsigned>& data_ptr, const BoxBounding& bound, const unsigned depth);

	node* LookUpNode(const Vec3& pos);

	std::vector<GameObject>* gameObject_list_ptr_;
public:
	ObjctOctree() = default;

	void BuildTree(std::vector<GameObject>* _gameObject_list_ptr, const BoxBounding& bound);

	//八叉树光线求交
	bool Intersect(const Ray& r);

	node* root_node_ptr_ = nullptr;
};


class TriangleOctree {

private:
	//八叉树节点数据
	struct node {
		//constructor
		node() = default;
		node(const std::vector<Triangle>& _data_index, const BoxBounding& _bound, const bool _is_leaf) :data_index(_data_index), boxbound(_bound), is_leaf(_is_leaf) {}
		node(const BoxBounding& _bound, const bool& _is_leaf) :boxbound(_bound), is_leaf(_is_leaf) {}
		//funaction
	public:
		void recursiveDestory(node* node);
		//destructor
		~node() {
			recursiveDestory(this);
		}
		//data
		std::vector<Triangle> data_index;
		BoxBounding boxbound;
		node* sub_node[8]{ nullptr };
		bool is_leaf = false;
	};

	node* OctreeBuild(const std::vector<Triangle>& triangle_index, const BoxBounding& bound, const unsigned depth);

	GameObject* obj_ptr_ = nullptr;
public:
	TriangleOctree() = default;

	void BuildTree();

	node* root_node_ptr_ = nullptr;
};

#endif // ! OCTREE_H_
