#ifndef BMATH_H_
#define BMATH_H_
#include "vec3.h"

inline Vec3 Cross(const Vec3& a,const Vec3& b) {
	return Vec3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y);
}

inline float Dot(const Vec3& a, const Vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

#endif // !BMATH_H_H

