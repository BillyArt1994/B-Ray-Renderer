#ifndef bounding_H_
#define bounding_H_
#include "vec3.h"
#include "triangle.h"
#include "ray.h"
#include <array>

class Bounding {
public:

	virtual void BuildBound(const std::vector<Vertex>& _vert) = 0;
	//intersection function
	virtual bool Intersect(const Ray& r, float& t)const = 0;
};

class BoxBounding :public Bounding
{
public:
	//constructor
	BoxBounding() = default;
	BoxBounding(const Vec3& _minp, const Vec3& _maxp) :length_(Abs(_minp.x)+ Abs(_maxp.x)), cet_pos_((_minp + _maxp) * 0.5) {}
	//funaction
	std::array<BoxBounding, 8> GetEightSubBoxBounding()const;
	bool CheckIfInside(const Vec3& point) const;
	bool CheckIfInside(const Vec3& point1, const Vec3& point2, const Vec3& point3) const;
	bool CheckIfinside(const SphereBounding& sp_bounding) const;
	void BuildBound(const std::vector<Vertex>& _vert);
	bool Intersect(const Ray& r, float& t) const;

	//data
	float length_;
	Vec3 cet_pos_;
};

class SphereBounding :public Bounding
{
public:
	//constructor
	SphereBounding() = default;
	//funaction
	bool CheckIfInside(const SphereBounding& _bounding) const;
	void BuildBound(std::vector<Vertex>& _vert);
	bool Intersect(const Ray& r, float& t) const;
	//data
	float radius_ = 0.0f;
	Vec3 cet_pos_;
};

#endif // !bounding_H_
