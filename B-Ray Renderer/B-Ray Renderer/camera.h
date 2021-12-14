#ifndef CAMERA_H_
#define CAMERA_H_
#include "transform.h"

struct Camera
{
	//constructor
	Camera() = default;
	Camera(const Vec3& _pos,const float& _clip) :transform_(_pos),clip(_clip){}
	//data
	Transform transform_;
	float clip = 1.0f;
};


#endif // ! CAMERA_H_

