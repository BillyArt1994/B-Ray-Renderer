#ifndef AABB_H_
#define AABB_H_
#include "vec3.h"
#include <array>

class AABB {
public:
	//constructor
	AABB() = default;
	AABB(Vec3 _minp,Vec3 _maxp):minpoint_(_minp), maxpoint_(_maxp){}

	//funaction
	std::array<AABB, 8> GetEightSubAABB()const;
	bool checkIfInside(const Vec3& point) const;
	//data
	Vec3 minpoint_;
	Vec3 maxpoint_;
};


#endif // !AABB_H_
