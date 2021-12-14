#ifndef AABB_H_
#define AABB_H_
#include "vec3.h"

class AABB {
public:
	AABB() = default;
	AABB(Vec3 _minp,Vec3 _maxp):minpoint_(_minp), maxpoint_(_maxp){}
	Vec3 minpoint_;
	Vec3 maxpoint_;
};


#endif // !AABB_H_
