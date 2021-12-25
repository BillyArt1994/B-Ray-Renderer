#ifndef BMATH_H_
#define BMATH_H_
#include "vec3.h"

inline Vec3 Cross(const Vec3& a,const Vec3& b) noexcept {
	return Vec3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y);
}

inline float Dot(const Vec3& a, const Vec3& b)noexcept {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Distance(const Vec3& a, const Vec3& b)noexcept {
	return sqrt(Dot(a, b));
}

template<typename T>
constexpr T Max(const T& x, const T& y) noexcept {
	return x > y ? x : y;
}

template<typename T>
constexpr T Max(const T& x, const T& y, const T& z) noexcept {
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

template<typename T>
constexpr T Min(const T& x, const T& y) noexcept {
	return x > y ? x : y;
}

template<typename T>
constexpr T Min(const T& x, const T& y , const T& z) noexcept {
	return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

constexpr float Clamp(const float& x, const float& min, const float& max)noexcept {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

constexpr float Saturate(const float& x) noexcept {
	if (x > 1)return 1.0f;
	if (x < 0)return 0.0f;
	return x;
}

inline float Abs(float x) noexcept { return x < 0 ? -x : x; }

constexpr int Nearest2Power(int i) {
	i |= (i >> 1);
	i |= (i >> 2);
	i |= (i >> 4);
	i |= (i >> 8);
	i |= (i >> 16);
	return i + 1;
}

#endif // !BMATH_H_H

