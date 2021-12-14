#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "ray.h"
#include "vertex.h"
#include "bmath.h"
#include <vector>

class Triangle {
public:
	//constructor
	Triangle() = default;
	constexpr Triangle (const unsigned& _v1, const unsigned& _v2, const unsigned& _v3):idx1_(_v1), idx2_(_v2),idx3_(_v3){}
	//funaction

	// data
	Vec3 normal_;
	union
	{
		struct 
		{
			unsigned idx1_,idx2_,idx3_;
		};
		unsigned index_[3]{0};
	};


};
#endif // !TRIANGLE_H_
