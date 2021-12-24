#include "bounding.h"

std::array<BoxBounding, 8> BoxBounding::GetEightSubBoxBounding()const {
	std::array<BoxBounding, 8> subBound;
	const float length = (maxpoint_.x - minpoint_.x) / 2;
	const Vec3 maxPfourB = maxpoint_;
	const Vec3 minPfourB = maxpoint_ - length;
	subBound[0].maxpoint_ = maxPfourB;
	subBound[0].minpoint_ = minPfourB;
	subBound[1].maxpoint_ = maxPfourB - Vec3(length, 0, 0);
	subBound[1].minpoint_ = minPfourB - Vec3(length, 0, 0);
	subBound[2].maxpoint_ = maxPfourB - Vec3(0, length, 0);
	subBound[2].minpoint_ = minPfourB - Vec3(0, length, 0);
	subBound[3].maxpoint_ = maxPfourB - Vec3(length, length, 0);
	subBound[3].minpoint_ = minPfourB - Vec3(length, length, 0);
	subBound[4].maxpoint_ = maxPfourB - Vec3(0, 0, length);
	subBound[4].minpoint_ = minPfourB - Vec3(0, 0, length);
	subBound[5].maxpoint_ = maxPfourB - Vec3(length, 0, length);
	subBound[5].minpoint_ = minPfourB - Vec3(length, 0, length);
	subBound[6].maxpoint_ = maxPfourB - Vec3(0, length, length);
	subBound[6].minpoint_ = minPfourB - Vec3(0, length, length);
	subBound[7].maxpoint_ = maxPfourB - Vec3(length, length, length);
	subBound[7].minpoint_ = minPfourB - Vec3(length, length, length);
	return subBound;
}

bool BoxBounding::CheckIfInside(const BoxBounding& boxBound) const {

	return (minpoint_.x <= boxBound.maxpoint_.x && maxpoint_.x >= boxBound.minpoint_.x) &&
		(minpoint_.y <= boxBound.maxpoint_.y && maxpoint_.y >= boxBound.minpoint_.y) &&
		(minpoint_.z <= boxBound.maxpoint_.z && maxpoint_.z >= boxBound.minpoint_.z);
}

bool BoxBounding::CheckIfInside(const Vec3& point) const {
	if (point.x > maxpoint_.x || point.y > maxpoint_.y || point.z > maxpoint_.z ||
		point.x < minpoint_.x || point.y < minpoint_.y || point.z < minpoint_.z) return false;
	return true;
}

void BoxBounding::BuildBound(const std::vector<Vertex>& _vert) {
	Vec3 minpoint_(FLT_MAX),maxpoint_(FLT_MIN);
	for (const Vertex& i: _vert)
	{
		minpoint_.x = Min(i.position.v[0], minpoint_.x);
		minpoint_.y = Min(i.position.v[1], minpoint_.y);
		minpoint_.z = Min(i.position.v[2], minpoint_.z);
		maxpoint_.x = Max(i.position.v[0], minpoint_.x);
		maxpoint_.y = Max(i.position.v[1], minpoint_.y);
		maxpoint_.z = Max(i.position.v[2], minpoint_.z);
	}
	minpoint_ = minpoint_;
	maxpoint_ = maxpoint_;
}

bool BoxBounding::Intersect(const Ray& r, float& t) const {
	const Vec3 maxpoint_ = maxpoint_;
	const Vec3 minpoint_ = minpoint_;
	const Vec3 rd(r.get_direction_());
	const Vec3 rp(r.get_orginPos_());
	const Vec3 invdir = 1 / rd;
	float tmin = 0.0f, tmax = 0.0f, tminY = 0.0f, tmaxY = 0.0f, tminZ = 0.0f, tmaxZ = 0.0f;

	if (invdir.x != invdir.x)
	{
		if (rp.x > maxpoint_.x || rp.x < minpoint_.x)
		{
			return false;
		}
		tmin = -FLT_MAX;
		tmax = FLT_MAX;
	}
	tmin = (minpoint_.x - rp.x) * invdir.x;
	tmax = (maxpoint_.x - rp.x) * invdir.x;
	if (tmin > tmax) std::swap(tmin, tmax);

	if (invdir.y != invdir.y)
	{
		if (rp.y > maxpoint_.y || rp.y < minpoint_.y)
		{
			return false;
		}
		tminY = -FLT_MAX;
		tmaxY = FLT_MAX;
	}
	tminY = (minpoint_.y - rp.y) * invdir.y;
	tmaxY = (maxpoint_.y - rp.y) * invdir.y;
	if (tminY > tmaxY) std::swap(tminY, tmaxY);

	if (tmaxY < tmax)
	{
		tmax = tmaxY;
	}

	if (tminY > tmin)
	{
		tmin = tminY;
	}

	if (invdir.z != invdir.z)
	{
		if (rp.z > maxpoint_.z || rp.z < minpoint_.z)
		{
			return false;
		}
		tminZ = -FLT_MAX;
		tmaxZ = FLT_MAX;
	}

	tminZ = (minpoint_.z - rp.z) * invdir.z;
	tmaxZ = (maxpoint_.z - rp.z) * invdir.z;

	if (tminZ > tmaxZ) std::swap(tminZ, tmaxZ);

	if (tmaxZ < tmax)
	{
		tmax = tmaxZ;
	}

	if (tminZ > tmin)
	{
		tmin = tminZ;
	}

	t = tmax;
	return true;
}

void SphereBounding::BuildBound(const std::vector<Vertex>& _vert) {
	Vec3 minpoint_(FLT_MAX), maxpoint_(FLT_MIN);
	for (const Vertex& i : _vert)
	{
		minpoint_.x = Min(i.position.v[0], minpoint_.x);
		minpoint_.y = Min(i.position.v[1], minpoint_.y);
		minpoint_.z = Min(i.position.v[2], minpoint_.z);
		maxpoint_.x = Max(i.position.v[0], minpoint_.x);
		maxpoint_.y = Max(i.position.v[1], minpoint_.y);
		maxpoint_.z = Max(i.position.v[2], minpoint_.z);
	}
	radius_ = Distance(minpoint_, maxpoint_) * 0.5f;
	cet_pos_ = (minpoint_+ maxpoint_)*0.5f;
}

bool SphereBounding::Intersect(const Ray& r, float& t) const {
	return true;
}

bool SphereBounding::CheckIfInside(const BoxBounding& boxBound)const {
	const float maxpoint_dis_square = 
			(boxBound.maxpoint_.x - cet_pos_.x)* (boxBound.maxpoint_.x - cet_pos_.x)
		+(boxBound.maxpoint_.y - cet_pos_.y)* (boxBound.maxpoint_.y - cet_pos_.y)
		+(boxBound.maxpoint_.z - cet_pos_.z)* (boxBound.maxpoint_.z - cet_pos_.z);
	const float minpoint_dis_square =
		(boxBound.minpoint_.x - cet_pos_.x) * (boxBound.minpoint_.x - cet_pos_.x)
		+ (boxBound.minpoint_.y - cet_pos_.y) * (boxBound.minpoint_.y - cet_pos_.y)
		+ (boxBound.minpoint_.z - cet_pos_.z) * (boxBound.minpoint_.z - cet_pos_.z);
	const float radius_square = radius_ * radius_;
	return (maxpoint_dis_square<= radius_square || minpoint_dis_square<= radius_square);
}