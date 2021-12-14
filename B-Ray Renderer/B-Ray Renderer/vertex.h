#ifndef VERTEX_H_
#define VERTEX_H_

#include "Vec3.h"

struct Vertex
{
	//constructor
	Vertex() = default;
	constexpr Vertex(const Vec3& pos):position(pos){}
	//date
	Vec3 position;
	Vec3 normal;
	Vec3 uv;
	Color color;
};

#endif // !VERTEX_H_
