#ifndef bounding_H_
#define bounding_H_
#include "vec3.h"
#include "triangle.h"
#include "ray.h"
#include <array>

class Bounding {
public:

	virtual void BuildBound(const std::vector<Vertex>& _vert) {};
	//intersection function
	virtual bool Intersect(const Ray& r, float& t) { return true; };
};

class BoxBounding:public Bounding 
{
public:
	//constructor
	BoxBounding() = default;
	BoxBounding(Vec3 _minp, Vec3 _maxp) :minpoint_(_minp), maxpoint_(_maxp) {}
	//funaction
	std::array<BoxBounding, 8> GetEightSubBoxBounding()const;
	bool CheckIfInside(const Vec3& point) const;
	bool CheckIfInside(const Vec3& point1, const Vec3& point2, const Vec3& point3) const;
	void BuildBound(const std::vector<Vertex>& _vert);
	bool Intersect(const Ray& r, float& t);

	//data
	Vec3 minpoint_;
	Vec3 maxpoint_;
};

class SphereBounding:public Bounding
{
public:
	//constructor
	SphereBounding() = default;
	//funaction
	bool CheckIfInside(const Bounding& _bounding) const;
	void BuildBound(std::vector<Vertex>& _vert);
	bool Intersect(const Ray& r, float& t);
	//data
	float radius_ = 0.0f;
	Vec3 cet_pos_;
};

#endif // !bounding_H_
