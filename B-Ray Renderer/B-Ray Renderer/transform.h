#ifndef TRANSFORM_H_
#define TRANSFORM_H_
#include "vec3.h"

class Transform {
public:
	//constructor
	Transform() = default;
	Transform(const Vec3& pos, const Vec3& rot, const Vec3& scale) :
		position_(pos), rotation_(rot), scale_(scale) {}
	Transform(const Vec3& pos) :position_(pos) {}
	//funaction

	//data
	Vec3 position_;
	Vec3 rotation_;
	Vec3 scale_;

};

#endif // !TRANSFORM_H_
