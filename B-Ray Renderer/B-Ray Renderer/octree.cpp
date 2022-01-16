#include "Octree.h"

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

void Octree::OctreeBuild(node* node_ptr, std::vector<GameObject>* gameObject_array_ptr,const std::vector<unsigned>& index_array, const BoxBounding& bound, const unsigned depth){

	//������ݴ�С
	int length = index_array.size();

	//������ݵ������õ����ֵ���߰˲�����ȵ���������������˳���������Ҷ�ӽڵ�
	if (length <= maxcount || depth < 1)
	{
		node_ptr = new Octree::node(index_array, bound, true);
		return;
	}

	//��ð˸��Ӱ�Χ��
	std::array<BoxBounding, 8> subBounding = bound.GetEightSubBoxBounding();

	//�����˸���������
	std::vector<unsigned> data_array[8];

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			if ((*gameObject_array_ptr)[index_array[j]].bound_ptr_->Contains(subBounding[i]))
			{
				data_array[i].push_back(index_array[j]);
			}
		}
	}

	if (depth <= 31)
	{
		OctreeBuild(node_ptr->sub_node[7], gameObject_array_ptr, data_array[0], subBounding[0], depth - 1);
		OctreeBuild(node_ptr->sub_node[6], gameObject_array_ptr, data_array[1], subBounding[1], depth - 1);
		OctreeBuild(node_ptr->sub_node[5], gameObject_array_ptr, data_array[2], subBounding[2], depth - 1);
		OctreeBuild(node_ptr->sub_node[4], gameObject_array_ptr, data_array[3], subBounding[3], depth - 1);
		OctreeBuild(node_ptr->sub_node[3], gameObject_array_ptr, data_array[4], subBounding[4], depth - 1);
		OctreeBuild(node_ptr->sub_node[2], gameObject_array_ptr, data_array[5], subBounding[5], depth - 1);
		OctreeBuild(node_ptr->sub_node[1], gameObject_array_ptr, data_array[6], subBounding[6], depth - 1);
		OctreeBuild(node_ptr->sub_node[0], gameObject_array_ptr, data_array[7], subBounding[7], depth - 1);
	}
	else
	{
		OctreeBuild(node_ptr->sub_node[0], gameObject_array_ptr, data_array[0], subBounding[0], depth - 1);
		OctreeBuild(node_ptr->sub_node[1], gameObject_array_ptr, data_array[1], subBounding[1], depth - 1);
		OctreeBuild(node_ptr->sub_node[2], gameObject_array_ptr, data_array[2], subBounding[2], depth - 1);
		OctreeBuild(node_ptr->sub_node[3], gameObject_array_ptr, data_array[3], subBounding[3], depth - 1);
		OctreeBuild(node_ptr->sub_node[4], gameObject_array_ptr, data_array[4], subBounding[4], depth - 1);
		OctreeBuild(node_ptr->sub_node[5], gameObject_array_ptr, data_array[5], subBounding[5], depth - 1);
		OctreeBuild(node_ptr->sub_node[6], gameObject_array_ptr, data_array[6], subBounding[6], depth - 1);
		OctreeBuild(node_ptr->sub_node[7], gameObject_array_ptr, data_array[7], subBounding[7], depth - 1);
	}
	return;
}

void Octree::BuildTree(std::vector<GameObject>* _gameObject_array_ptr, const BoxBounding& bound) {

}

bool Octree::Intersect(const Ray& r) {
	Ray ray(r);
	node* node_ptr = nullptr;
	std::vector<unsigned> gameobject_index;
	float offset_t(0.0f), minDis(FLT_MAX), temp_t(0.0f);
	unsigned length = 0;
	while (root_node_ptr_->boxbound.Contains(ray.get_orginPos_()))//��������Ƿ��ڳ����ڲ�
	{
		offset_t = 0.0f;							//���ò���t_Step
		node_ptr = LookUpNode(ray.get_orginPos_()); //������ߵ�ǰ���ڽڵ�
		gameobject_index = node_ptr->data;				    //��õ�ǰ�ڵ�����
		length = gameobject_index.size();					//��������б�

		if (length)
		{
			for (size_t i = 0; i < length; i++)
			{
				if ((*gameObject_list_ptr_)[gameobject_index[i]].bound_ptr_->IntersectRay(ray, temp_t) && temp_t < minDis)				  //�����ݼ���ཻ���
				{
					minDis = temp_t;
				}
			}
			if (minDis != FLT_MAX) return true;
		}

		node_ptr->boxbound.IntersectRay(ray, offset_t);//��õ�ǰ�ڵ�������ĳ���

		ray.RayRun(offset_t + 0.001f);//���������һ��ƫ��ֵ��Խ����һ���ڵ���
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
