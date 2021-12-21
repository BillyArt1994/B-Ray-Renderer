#ifndef bounding_H_
#define bounding_H_
#include "vec3.h"
#include "triangle.h"
#include "ray.h"
#include <array>

class BoxBounding;
class Bounding {
public:

	virtual void BuildBound(const std::vector<Vertex>& _vert) = 0;
	//intersection function
	virtual bool Intersect(const Ray& r, float& t)const = 0;

	virtual bool CheckIfInside(const BoxBounding& boxBound)const = 0;
};

class BoxBounding :public Bounding
{
public:
	//constructor
	BoxBounding() = default;
	BoxBounding(const Vec3& _minp, const Vec3& _maxp) :length_(Abs(_minp.x)+ Abs(_maxp.x)), cet_pos_((_minp + _maxp) * 0.5) {}
	//funaction
	std::array<BoxBounding, 8> GetEightSubBoxBounding()const;

	virtual bool CheckIfInside(const BoxBounding& boxBound)const;
	virtual void BuildBound(const std::vector<Vertex>& _vert) override;
	virtual bool Intersect(const Ray& r, float& t) const override;
	bool CheckIfInside(const Vec3& point) const;


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
	virtual bool CheckIfInside(const BoxBounding& boxBound)const override;
	void BuildBound(std::vector<Vertex>& _vert);
	bool Intersect(const Ray& r, float& t) const;
	//data
	float radius_ = 0.0f;
	Vec3 cet_pos_;
};



#endif // !bounding_H_
