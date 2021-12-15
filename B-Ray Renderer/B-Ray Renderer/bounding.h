#ifndef bounding_H_
#define bounding_H_
#include "vec3.h"
#include "triangle.h"
#include <array>

class BoxBounding{
public:
	//constructor
	BoxBounding() = default;
	BoxBounding(Vec3 _minp, Vec3 _maxp) :minpoint_(_minp), maxpoint_(_maxp) {}
	//funaction
	std::array<BoxBounding, 8> GetEightSubBoxBounding()const;
	bool CheckIfInside(const Vec3& point) const;
	bool CheckIfInside(const Vec3& point1, const Vec3& point2, const Vec3& point3) const;
	void BuildBound(const std::vector<Vertex>& _vert);
	//data
	Vec3 minpoint_;
	Vec3 maxpoint_;
};

class SphereBounding
{
public:
	//constructor
	SphereBounding() = default;
	//funaction
	void BuildBound(std::vector<Vertex>& _vert);
	//data
	float radius_ = 0.0f;
	Vec3 cet_point_;
};

#endif // !bounding_H_
