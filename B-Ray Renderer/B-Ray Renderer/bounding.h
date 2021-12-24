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
	virtual void BuildBound(const Vertex& v1, const Vertex& v2, const Vertex& v3) = 0;
	//intersection function
	virtual bool Intersect(const Ray& r, float& t)const = 0;

	virtual bool CheckIfInside(const BoxBounding& boxBound)const = 0;
};

class BoxBounding :public Bounding
{
public:
	//constructor
	BoxBounding() = default;
	BoxBounding(const Vec3& _minp, const Vec3& _maxp) :minpoint_(_minp), maxpoint_(_maxp) {}
	//funaction
	std::array<BoxBounding, 8> GetEightSubBoxBounding()const;

	virtual bool CheckIfInside(const BoxBounding& boxBound)const;
	virtual void BuildBound(const std::vector<Vertex>& _vert) override;
	virtual void BuildBound(const Vertex& v1, const Vertex& v2, const Vertex& v3) override;
	virtual bool Intersect(const Ray& r, float& t) const override;
	bool CheckIfInside(const Vec3& point) const;


	//data
	Vec3 minpoint_;
	Vec3 maxpoint_;
};

class SphereBounding :public Bounding
{
public:
	//constructor
	SphereBounding() = default;
	//funaction
	virtual bool CheckIfInside(const BoxBounding& boxBound)const override;
	virtual void BuildBound(const std::vector<Vertex>& _vert) override;
	virtual void BuildBound(const Vertex& v1, const Vertex& v2, const Vertex& v3) override;
	virtual bool Intersect(const Ray& r, float& t) const override;
	//data
	float radius_ = 0.0f;
	Vec3 cet_pos_;
};



#endif // !bounding_H_
