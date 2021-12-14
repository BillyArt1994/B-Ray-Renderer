#ifndef MESH_H_
#define MESH_H_
#include "vertex.h"
#include "transform.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "triangle.h"

class Mesh {
public:
	//constructor
	Mesh() = default;
	Mesh(const std::string filename);
	//data
	Transform transform_;
	std::vector<Vertex> vertex_list_;
	std::vector<Triangle> triangle_list_;
	std::string name_;
	//function
	inline int get_face_count_()const {
		return triangle_list_.size() / 3;
	}

	inline int get_vertex_count_()const {
		return vertex_list_.size();
	}
};

#endif // !MESH_H_