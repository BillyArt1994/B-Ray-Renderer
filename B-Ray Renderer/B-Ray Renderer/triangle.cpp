#include "triangle.h"

void Triangle::BuildBounding(const std::vector<Vertex>& vertex_list) {
	bound_.BuildBound(vertex_list[idx1_], vertex_list[idx2_], vertex_list[idx3_]);
}