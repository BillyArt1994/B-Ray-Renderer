#include "octree.h"

void Octree::node::recursiveDestory(Octree::node* node) {
	if (node == nullptr)
		return;
	recursiveDestory(node->sub_node[0]);
	recursiveDestory(node->sub_node[1]);
	recursiveDestory(node->sub_node[2]);
	recursiveDestory(node->sub_node[3]);
	recursiveDestory(node->sub_node[4]);
	recursiveDestory(node->sub_node[5]);
	recursiveDestory(node->sub_node[6]);
	recursiveDestory(node->sub_node[7]);

	delete node;
	node = nullptr;
}

Octree::node* Octree::OctreeBuild(const std::vector<Hittable>& data_ptr, const BoxBounding& bound, const unsigned depth) {
	//获得数据大小
	int length = data_ptr.size();

	//如果数据低于设置的最大值或者八叉树深度低于1返回叶子节点
	if (length <= 1 || depth < 1)
	{
		Octree::node* leaf_node = new Octree::node(data_ptr, bound, true);
		return leaf_node;
	}

	Octree::node* curnode = new Octree::node(bound, true);
	//获得八个子包围盒
	std::array<BoxBounding, 8> subBounding = bound.GetEightSubBoxBounding();
	//创建八个数据数组
	std::vector<Hittable> data_array[8];

	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (subBounding[j].CheckIfInside(data_ptr[i].bound_))
			{
				data_array[j].push_back(data_ptr[i]);
			}
		}
	}

	if (depth <= 31)
	{
		curnode->sub_node[7] = OctreeBuild(data_array[0], subBounding[0], depth - 1);
		curnode->sub_node[6] = OctreeBuild(data_array[1], subBounding[1], depth - 1);
		curnode->sub_node[5] = OctreeBuild(data_array[2], subBounding[2], depth - 1);
		curnode->sub_node[4] = OctreeBuild(data_array[3], subBounding[3], depth - 1);
		curnode->sub_node[3] = OctreeBuild(data_array[4], subBounding[4], depth - 1);
		curnode->sub_node[2] = OctreeBuild(data_array[5], subBounding[5], depth - 1);
		curnode->sub_node[1] = OctreeBuild(data_array[6], subBounding[6], depth - 1);
		curnode->sub_node[0] = OctreeBuild(data_array[7], subBounding[7], depth - 1);
	}
	else
	{
		curnode->sub_node[0] = OctreeBuild(data_array[0], subBounding[0], depth - 1);
		curnode->sub_node[1] = OctreeBuild(data_array[1], subBounding[1], depth - 1);
		curnode->sub_node[2] = OctreeBuild(data_array[2], subBounding[2], depth - 1);
		curnode->sub_node[3] = OctreeBuild(data_array[3], subBounding[3], depth - 1);
		curnode->sub_node[4] = OctreeBuild(data_array[4], subBounding[4], depth - 1);
		curnode->sub_node[5] = OctreeBuild(data_array[5], subBounding[5], depth - 1);
		curnode->sub_node[6] = OctreeBuild(data_array[6], subBounding[6], depth - 1);
		curnode->sub_node[7] = OctreeBuild(data_array[7], subBounding[7], depth - 1);
	}
	return curnode;
}

void Octree::BuildTree(const std::vector<Hittable>& data_ptr, const BoxBounding& bound, const unsigned depth) {
	root_node_ptr_ = OctreeBuild(data_ptr,bound,depth);
}