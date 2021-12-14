#ifndef RAY_H_
#define RAY_H_
#include "vec3.h"

class Ray {
public:
	//constructor
	Ray() = default;
	Ray(const Ray& r) {
		orginPos_ = r.orginPos_;
		direction_ = r.direction_;
	}
	Ray(const Vec3& _pos ,const Vec3& _dir):orginPos_(_pos), direction_(_dir){}
	//funaction
	inline Vec3 get_orginPos_() const { return orginPos_; }
	inline Vec3 get_direction_() const { return direction_; }
private:
	//data
	Vec3 orginPos_;
	Vec3 direction_;
};

#endif // !RAY_H_

