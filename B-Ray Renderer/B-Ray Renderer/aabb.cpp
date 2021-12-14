#include "aabb.h"

std::array<AABB, 8> AABB::GetEightSubAABB()const {
		std::array<AABB, 8> subBound;
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

bool AABB::checkIfInside(const Vec3& point) const {
	if (point.x > maxpoint_.x || point.y > maxpoint_.y || point.z > maxpoint_.z ||
		point.x < minpoint_.x || point.y < minpoint_.y || point.z < minpoint_.z) return false;
	return true;
}