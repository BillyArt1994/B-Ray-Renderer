#ifndef bounding_H_
#define bounding_H_
#include "vec3.h"
#include "triangle.h"
#include "ray.h"
#include "mesh.h"
#include <array>

class BoxBounding;
class Bounds{
public:
	//intersection function
	virtual bool IntersectRay(const Ray& r, float& t)const = 0;
	virtual bool Contains(const BoxBounding& boxBound)const = 0;
};

class BoxBounding :public Bounds
{
public:
	//constructor
	BoxBounding(std::vector<Vertex>& _vert_list);
	BoxBounding() = default;
	BoxBounding(const Vec3& _minp, const Vec3& _maxp) :minpoint_(_minp), maxpoint_(_maxp) {}
	//funaction
	std::array<BoxBounding, 8> GetEightSubBoxBounding()const;
	virtual bool Contains(const BoxBounding& boxBound)const;
	bool Contains(const Vec3& point) const;
	virtual bool IntersectRay(const Ray& r, float& t) const override;
	
	//data
	Vec3 minpoint_;
	Vec3 maxpoint_;
};

class SphereBounding :public Bounds
{
public:
	//constructor
	SphereBounding() = default;
	SphereBounding(std::vector<Vertex>& _vert_list);
	SphereBounding(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	//funaction
	virtual bool Contains(const BoxBounding& boxBound)const override;
	bool Contains(const Vec3& point) const;
	virtual bool IntersectRay(const Ray& r, float& t) const override;
	//data
	float radius_ = 0.0f;
	Vec3 cet_pos_;
};



#endif // !bounding_H_
