#include "triangle.h"

bool Triangle::Intersect(const Ray& ray, float& t, std::vector<Vertex>& vertarray) {
	const Vec3 E1(vertarray[idx2_].position - vertarray[idx1_].position),
		E2(vertarray[idx3_].position - vertarray[idx1_].position),
		dir(ray.get_direction_()),
		P = Cross(dir, E2),
		T = dir - vertarray[idx1_].position;
	const float det = Dot(E1, P), inv_det(1.0f / det),
		u = Dot(T, P) * inv_det;

	if (u < 0.0f || u>1.0f) return false;
	const Vec3 Q = Cross(T, E1);
	const float v = Dot(dir, Q) * inv_det;
	if (v < 0.0f || v + u>1.0f) return false;
	t = Dot(E2, Q) * inv_det;
	return true;
}