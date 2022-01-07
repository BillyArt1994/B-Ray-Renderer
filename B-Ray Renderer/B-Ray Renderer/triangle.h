#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "vertex.h"
#include "bmath.h"
#include <vector>
#include "bounding.h"

class Triangle {
public:

	//constructor
	Triangle() = default;
	Triangle (const unsigned& _v1, const unsigned& _v2, const unsigned& _v3):idx1_(_v1), idx2_(_v2),idx3_(_v3){}

	//funaction
	void BuildBounding(const std::vector<Vertex>& vertex_list);

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

	SphereBounding bound_;
};
#endif // !TRIANGLE_H_
