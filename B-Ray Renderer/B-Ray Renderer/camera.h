#ifndef CAMERA_H_
#define CAMERA_H_
#include "transform.h"
#include "displayManager.h"

struct Camera
{
	//constructor
	Camera() = default;
	Camera(const Vec3& _pos,const float _clip,const float viewport_width) :
		transform_(_pos),
		clip(_clip),
		horizontal_(Vec3(0.0f, viewport_width,0.0f) ),
		vertical_(Vec3(viewport_width/ DisplayManager::SCREEN_ASPECT_RATIO, 0.0f, 0.0f)),
		low_left_corner_(transform_.position_- horizontal_*0.5f- vertical_*0.5f+ Vec3(0.0f, 0.0f, clip)){}
	//data
	Transform transform_;
	float clip = 1.0f;
	Vec3 low_left_corner_;
	Vec3 vertical_;
	Vec3 horizontal_;
};


#endif // ! CAMERA_H_

