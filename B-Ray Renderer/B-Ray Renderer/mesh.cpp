#include "mesh.h"

Mesh::Mesh(const std::string filename) {
	std::ifstream ifs;
	ifs.open(filename, std::ios::in);
	if (ifs.fail()) return;
	std::string line;
	std::vector<Vec3> normallist;
	std::vector<Vec3> texcoordlist;
	float x, y, z;
	const char* c_line;
	while (std::getline(ifs, line))
	{
		c_line = line.c_str();
		switch (c_line[0])
		{
		case '#':
			if (c_line[2] == 'o' && c_line[1]!= '\0')
			{
				name_ = line.substr(8);
			}
			break;
		case 'v':
			if (c_line[1] == ' ')
			{
				sscanf_s(c_line, "v %f %f %f", &x, &y, &z);
				vertex_list_.push_back(Vec3(x, y, z));
			}
			if (c_line[1] == 'n')
			{
				sscanf_s(c_line, "vn %f %f %f", &x, &y, &z);
				normallist.push_back(Vec3(x, y, z));
			}
			if (c_line[1] == 't')
			{
				sscanf_s(c_line, "vt %f %f %f", &x, &y, &z);
				texcoordlist.push_back(Vec3(x, y, z));
			}
			break;

		case 'f':
			int vertex_index[3], uv_index[3], normal_index[3];
			sscanf_s(c_line, "f %u/%u/%u %u/%u/%u %u/%u/%u",
				&vertex_index[0], &uv_index[0], &normal_index[0],
				&vertex_index[1], &uv_index[1], &normal_index[1],
				&vertex_index[2], &uv_index[2], &normal_index[2]);
			triangle_list_.push_back(Triangle(vertex_index[0], vertex_index[1], vertex_index[2]));
			for (size_t i = 0; i < 3; i++)
			{
				vertex_list_[vertex_index[i]-=1u].uv = texcoordlist[uv_index[i]-=1u];
				vertex_list_[vertex_index[i]-=1u].normal = normallist[normal_index[i]-=1u];
			}
			break;
		}
	}
	ifs.close();
}