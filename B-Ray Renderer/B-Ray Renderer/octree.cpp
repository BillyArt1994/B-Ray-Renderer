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

Octree::node* Octree::OctreeBuild(const std::vector<Hittable*>& data_ptr, const BoxBounding& bound, const unsigned depth) {
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
	std::vector<Hittable*> data_array[8];

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			if (data_ptr[j]->bound_ptr_->CheckIfInside(subBounding[i]))
			{
				data_array[i].push_back(data_ptr[j]);
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

void Octree::BuildTree(const std::vector<Hittable*>& data_ptr, const BoxBounding& bound, const unsigned depth) {
	root_node_ptr_ = OctreeBuild(data_ptr, bound, depth);
}

bool Octree::Intersect(const Ray& r) {
	Ray ray(r);
	node* node_ptr = nullptr;
	std::vector<Hittable*> hittable;
	float offset_t(0.0f), minDis(FLT_MAX),temp_t(0.0f);
	unsigned length = 0;
	while (root_node_ptr_->boxbound.CheckIfInside(ray.get_orginPos_()))//检测射线是否还在场景内部
	{
		offset_t = 0.0f;							//重置步进t_Step
		node_ptr = LookUpNode(ray.get_orginPos_()); //获得射线当前所在节点
		hittable = node_ptr->data;				    //获得当前节点数据
		length = hittable.size();					//获得数据大小

		if (length)
		{
			for (size_t i = 0; i < length; i++)
			{
				if (hittable[i]->bound_ptr_->Intersect(ray, temp_t) && temp_t < minDis)				  //与数据检测相交与否
				{
					minDis = temp_t;
				}
			}
			if(minDis != FLT_MAX) return true;
		}

		node_ptr->boxbound.Intersect(ray, offset_t);//获得当前节点立方体的出口

		ray.RayRun(offset_t + 0.001f);//给光线添加一个偏移值穿越到下一个节点中
	}
	return false;
}

Octree::node* Octree::LookUpNode(const Vec3& pos) {
	const int x = floor(pos.x), y = floor(pos.y), z = floor(pos.z);
	node* node_ptr = nullptr;
	unsigned i(31);
	do
	{
		node_ptr = node_ptr->sub_node[((x >> i) & 1) + (((y >> i) & 1) << 1) + (((z >> i) & 1) << 2)];
		--i;
	} while (!node_ptr->is_leaf);
	return node_ptr;
}