#ifndef VERTEX_H_
#define VERTEX_H_

#include "Vec3.h"

struct Vertex
{
	//constructor
	Vertex() = default;
	Vertex(const Vec3& pos):position(pos){}
	//funcation
	//date
	Vec3 position;
	Vec3 normal;
	Vec3 uv;
	Color color;
};

#endif // !VERTEX_H_
