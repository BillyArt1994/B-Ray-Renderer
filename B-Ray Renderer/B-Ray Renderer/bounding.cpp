#include "bounding.h"

std::array<BoxBounding, 8> BoxBounding::GetEightSubBoxBounding()const {
	std::array<BoxBounding, 8> subBound;
	const float quarter_length = length_ * 0.25f;
	subBound[0].cet_pos_ = cet_pos_ + quarter_length;
	subBound[0].length_ = quarter_length;
	subBound[1].cet_pos_ = cet_pos_ + Vec3(-quarter_length, quarter_length, quarter_length) ;
	subBound[1].length_ = quarter_length;
	subBound[2].cet_pos_ = cet_pos_ + Vec3(quarter_length, -quarter_length, quarter_length);
	subBound[2].length_ = quarter_length;
	subBound[3].cet_pos_ = cet_pos_ + Vec3(-quarter_length, -quarter_length, quarter_length);
	subBound[3].length_ = quarter_length;
	subBound[4].cet_pos_ = cet_pos_ + Vec3(quarter_length, quarter_length, -quarter_length);
	subBound[4].length_ = quarter_length;
	subBound[5].cet_pos_ = cet_pos_ + Vec3(-quarter_length, quarter_length, -quarter_length);
	subBound[5].length_ = quarter_length;
	subBound[6].cet_pos_ = cet_pos_ + Vec3(quarter_length, -quarter_length, -quarter_length);
	subBound[6].length_ = quarter_length;
	subBound[7].cet_pos_ = cet_pos_ - quarter_length;
	subBound[7].length_ = quarter_length;
	return subBound;
}

bool BoxBounding::CheckIfInside(const BoxBounding& boxBound) const {
	const Vec3 maxPoint = cet_pos_ + length_;
	const Vec3 minPoint = cet_pos_ - length_;
	const Vec3 boxBound_maxPoint = boxBound.cet_pos_ + boxBound.length_;
	const Vec3 boxBound_minPoint = boxBound.cet_pos_ - boxBound.length_;
	return (minPoint.x <= boxBound_maxPoint.x && maxPoint.x >= boxBound_minPoint.x) &&
		(minPoint.y <= boxBound_maxPoint.y && maxPoint.y >= boxBound_minPoint.y) &&
		(minPoint.z <= boxBound_maxPoint.z && maxPoint.z >= boxBound_minPoint.z);
}

bool BoxBounding::CheckIfInside(const Vec3& point) const {
	const Vec3 maxPoint = cet_pos_ + length_;
	const Vec3 minPoint = cet_pos_ - length_;
	if (point.x > maxPoint.x || point.y > maxPoint.y || point.z > maxPoint.z ||
		point.x < minPoint.x || point.y < minPoint.y || point.z < minPoint.z) return false;
	return true;
}

void BoxBounding::BuildBound(const std::vector<Vertex>& _vert) {
	Vec3 minpoint(FLT_MAX),maxpoint(FLT_MIN);
	for (const Vertex& i: _vert)
	{
		minpoint.x = Min(i.position.v[0], minpoint.x);
		minpoint.y = Min(i.position.v[1], minpoint.y);
		minpoint.z = Min(i.position.v[2], minpoint.z);
		maxpoint.x = Max(i.position.v[0], minpoint.x);
		maxpoint.y = Max(i.position.v[1], minpoint.y);
		maxpoint.z = Max(i.position.v[2], minpoint.z);
	}
	minpoint = minpoint;
	maxpoint = maxpoint;
}

bool BoxBounding::Intersect(const Ray& r, float& t) const {
	const Vec3 maxpoint = cet_pos_ + length_;
	const Vec3 minpoint = cet_pos_ - length_;
	const Vec3 rd(r.get_direction_());
	const Vec3 rp(r.get_orginPos_());
	const Vec3 invdir = 1 / rd;
	float tmin = 0.0f, tmax = 0.0f, tminY = 0.0f, tmaxY = 0.0f, tminZ = 0.0f, tmaxZ = 0.0f;

	if (invdir.x != invdir.x)
	{
		if (rp.x > maxpoint.x || rp.x < minpoint.x)
		{
			return false;
		}
		tmin = -FLT_MAX;
		tmax = FLT_MAX;
	}
	tmin = (minpoint.x - rp.x) * invdir.x;
	tmax = (maxpoint.x - rp.x) * invdir.x;
	if (tmin > tmax) std::swap(tmin, tmax);

	if (invdir.y != invdir.y)
	{
		if (rp.y > maxpoint.y || rp.y < minpoint.y)
		{
			return false;
		}
		tminY = -FLT_MAX;
		tmaxY = FLT_MAX;
	}
	tminY = (minpoint.y - rp.y) * invdir.y;
	tmaxY = (maxpoint.y - rp.y) * invdir.y;
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
		if (rp.z > maxpoint.z || rp.z < minpoint.z)
		{
			return false;
		}
		tminZ = -FLT_MAX;
		tmaxZ = FLT_MAX;
	}

	tminZ = (minpoint.z - rp.z) * invdir.z;
	tmaxZ = (maxpoint.z - rp.z) * invdir.z;

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

void SphereBounding::BuildBound(std::vector<Vertex>& _vert) {
	Vec3 minpoint(FLT_MAX), maxpoint(FLT_MIN);
	for (const Vertex& i : _vert)
	{
		minpoint.x = Min(i.position.v[0], minpoint.x);
		minpoint.y = Min(i.position.v[1], minpoint.y);
		minpoint.z = Min(i.position.v[2], minpoint.z);
		maxpoint.x = Max(i.position.v[0], minpoint.x);
		maxpoint.y = Max(i.position.v[1], minpoint.y);
		maxpoint.z = Max(i.position.v[2], minpoint.z);
	}
	radius_ = Distance(minpoint, maxpoint) * 0.5f;
	cet_pos_ = (minpoint+ maxpoint)*0.5f;
}

bool SphereBounding::Intersect(const Ray& r, float& t) const {
	return true;
}

bool SphereBounding::CheckIfInside(const BoxBounding& boxBound)const {
	const Vec3 boxBound_maxPoint = boxBound.cet_pos_ + boxBound.length_;
	const Vec3 boxBound_minPoint = boxBound.cet_pos_ - boxBound.length_;
	const float maxpoint_dis_square = 
			(boxBound_maxPoint.x - cet_pos_.x)* (boxBound_maxPoint.x - cet_pos_.x)
		+(boxBound_maxPoint.y - cet_pos_.y)* (boxBound_maxPoint.y - cet_pos_.y)
		+(boxBound_maxPoint.z - cet_pos_.z)* (boxBound_maxPoint.z - cet_pos_.z);
	const float minpoint_dis_square =
		(boxBound_minPoint.x - cet_pos_.x) * (boxBound_minPoint.x - cet_pos_.x)
		+ (boxBound_minPoint.y - cet_pos_.y) * (boxBound_minPoint.y - cet_pos_.y)
		+ (boxBound_minPoint.z - cet_pos_.z) * (boxBound_minPoint.z - cet_pos_.z);
	const float radius_square = radius_ * radius_;
	return (maxpoint_dis_square<= radius_square || minpoint_dis_square<= radius_square);
}