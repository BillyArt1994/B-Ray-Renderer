#ifndef  OCTREE_H_
#define OCTREE_H_
#include "aabb.h"
#include <vector>

template<typename T>
class Octree {
public:
	void OctreeBuild(vector<T>& data_ptr, AABB& bound, unsigned depth) {

		if (data_ptr.size() <= 1 || depth < 1)
		{
			node<T>* node = new OcterNode<T>(data_ptr,bound, true);
			return node;
		}

		OcterNode<T>* cur = new OcterNode<T>(bound, false);
		array<AABB, 8> subBounding = bound.getEightSubAABB();
		vector<T> dataArray[8];

		for (unsigned i = 0; i < length; i++)
		{
			for (unsigned j = 0; j < 8; j++)
			{
				if (subBounding[j].checkIfInside(data_ptr[i]))
				{
					dataArray[j].push_back(data_ptr[i]);
				}
			}
		}

		if (depth <= 31)
		{
			cur->m_children[7] = octreeBuild(objArray[0], subBounding[0], depth - 1);
			cur->m_children[6] = octreeBuild(objArray[1], subBounding[1], depth - 1);
			cur->m_children[5] = octreeBuild(objArray[2], subBounding[2], depth - 1);
			cur->m_children[4] = octreeBuild(objArray[3], subBounding[3], depth - 1);
			cur->m_children[3] = octreeBuild(objArray[4], subBounding[4], depth - 1);
			cur->m_children[2] = octreeBuild(objArray[5], subBounding[5], depth - 1);
			cur->m_children[1] = octreeBuild(objArray[6], subBounding[6], depth - 1);
			cur->m_children[0] = octreeBuild(objArray[7], subBounding[7], depth - 1);
		}
		else
		{
			cur->m_children[0] = octreeBuild(objArray[0], subBounding[0], depth - 1);
			cur->m_children[1] = octreeBuild(objArray[1], subBounding[1], depth - 1);
			cur->m_children[2] = octreeBuild(objArray[2], subBounding[2], depth - 1);
			cur->m_children[3] = octreeBuild(objArray[3], subBounding[3], depth - 1);
			cur->m_children[4] = octreeBuild(objArray[4], subBounding[4], depth - 1);
			cur->m_children[5] = octreeBuild(objArray[5], subBounding[5], depth - 1);
			cur->m_children[6] = octreeBuild(objArray[6], subBounding[6], depth - 1);
			cur->m_children[7] = octreeBuild(objArray[7], subBounding[7], depth - 1);
		}
		return cur;
	}

private:
	struct node {
		//constructor
		node(std::vector<T>& _data, AABB& _bound, bool _is_leaf) :data(_data), bound(_bound), is_leaf(_is_leaf){}
		node(AABB& _bound, bool _is_leaf) :bound(_bound), is_leaf(_is_leaf) {}
		//data
		std::vector<T> data;
		AABB bound;
		node* child_node[8]{ nullptr };
		bool is_leaf = false;
	};

	node* rootnode_ = nullptr;
};

#endif // ! OCTREE_H_
