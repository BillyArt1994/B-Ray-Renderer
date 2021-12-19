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

bool BoxBounding::CheckIfInside(const Vec3& point) const {
	if (point.x > maxpoint_.x || point.y > maxpoint_.y || point.z > maxpoint_.z ||
		point.x < minpoint_.x || point.y < minpoint_.y || point.z < minpoint_.z) return false;
	return true;
}

bool BoxBounding::CheckIfInside(const Vec3& point1, const Vec3& point2, const Vec3& point3) const {
	Vec3 v0(point1), v1(point2), v2(point3);

	if (CheckIfInside(v0) || CheckIfInside(v1) || CheckIfInside(v2))
	{
		return true;
	}

	const Vec3 e((maxpoint_.x - minpoint_.x) / 2), c(maxpoint_ - e);

	v0 -= c;
	v1 -= c;
	v2 -= c;

	const Vec3 boxNormal[3]{
		Vec3(1.0f, 0.0f, 0.0f),Vec3(0.0f, 1.0f, 0.0f),Vec3(0.0f, 0.0f, 1.0f) };
	const Vec3 tirgleEdge[3]{ v1 - v0,v2 - v1,v0 - v2 };
	const Vec3 axisArray[13] = {
		boxNormal[0],boxNormal[1],boxNormal[2],
		Cross(tirgleEdge[0],tirgleEdge[1]),
		Cross(boxNormal[0],tirgleEdge[0]), Cross(boxNormal[0], tirgleEdge[1]), Cross(boxNormal[0], tirgleEdge[2]),
		Cross(boxNormal[1],tirgleEdge[0]), Cross(boxNormal[1], tirgleEdge[1]), Cross(boxNormal[1], tirgleEdge[2]),
		Cross(boxNormal[2],tirgleEdge[0]), Cross(boxNormal[2], tirgleEdge[1]), Cross(boxNormal[2], tirgleEdge[2]),
	};

	for (int i = 0; i < 13; i++)
	{
		const float p0 = Dot(v0, axisArray[i]);
		const float p1 = Dot(v1, axisArray[i]);
		const float p2 = Dot(v2, axisArray[i]);

		const float r = e.x * abs(Dot(boxNormal[0], axisArray[i])) +
			e.y * abs(Dot(boxNormal[1], axisArray[i])) +
			e.z * abs(Dot(boxNormal[2], axisArray[i]));

		if (Min(p0, p1, p2) > r || -Max(p0, p1, p2) > r)
		{
			return false;
		}
	}
	return true;
}

bool BoxBounding::CheckIfinside(const SphereBounding& sp_bounding)const  {
	return Distance(cet_pos_, sp_bounding.cet_pos_) - (length_ + sp_bounding.radius_) <= 0.0001f ? true : false;
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

void SphereBounding::BuildBound(std::vector<Vertex>& _vert) {
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