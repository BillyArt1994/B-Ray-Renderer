#ifndef LIGHT_H_
#define LIGHT_H_
#include "transform.h"
#include "vec3.h"

class Light {
public:
	Color color_;
	Transform transform_;
};

#endif // !LIGHT_H_
