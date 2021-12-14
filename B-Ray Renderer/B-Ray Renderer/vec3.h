#ifndef VEC3_H_
#define VEC3_H_

#include <iostream>

struct Vec3 {
	//constructor
	Vec3() = default;
	constexpr Vec3(const float& _x, const float& _y, const float& _z) :x(_x), y(_y), z(_z) {}
	constexpr Vec3(const Vec3& b) :x(b.x), y(b.y), z(b.z) {}
	constexpr explicit  Vec3(const float& _value) :x(_value), y(_value), z(_value) {}

	//operator
	inline Vec3 operator +(const Vec3& b) const {
		return Vec3(x + b.x, y + b.y, z + b.z);
	}

	inline Vec3 operator -(const Vec3& b) const {
		return Vec3(x - b.x, y - b.y, z - b.z);
	}

	inline Vec3 operator *(const Vec3& b) const {
		return Vec3(x * b.x, y * b.y, z * b.z);
	}

	inline Vec3 operator /(const Vec3& b) const {
		return Vec3(x / b.x, y / b.y, z / b.z);
	}

	inline Vec3& operator +=(const Vec3& b) {
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	inline Vec3& operator -=(const Vec3& b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}

	inline Vec3& operator *=(const Vec3& b) {
		x *= b.x;
		y *= b.y;
		z *= b.z;
		return *this;
	}

	inline Vec3& operator /=(const Vec3& b) {
		x /= b.x;
		y /= b.y;
		z /= b.z;
		return *this;
	}

	inline Vec3 operator + (const float& b)const {
		return Vec3(x + b, y + b, z + b);
	}

	inline Vec3 operator - (const float& b)const {
		return Vec3(x - b, y - b, z - b);
	}

	inline Vec3 operator * (const float& b)const {
		return Vec3(x * b, y * b, z * b);
	}

	inline Vec3 operator / (const float& b)const {
		return Vec3(x / b, y / b, z / b);
	}

	inline Vec3& operator += (const float& b) {
		x += b;
		y += b;
		z += b;
		return *this;
	}

	inline Vec3& operator -= (const float& b) {
		x -= b;
		y -= b;
		z -= b;
		return *this;
	}

	inline Vec3& operator *= (const float& b) {
		x *= b;
		y *= b;
		z *= b;
		return *this;
	}

	inline Vec3& operator /= (const float& b) {
		x /= b;
		y /= b;
		z /= b;
		return *this;
	}

	inline Vec3& operator =(const Vec3& b) {
		x = b.x;
		y = b.y;
		z = b.z;
		return *this;
	}

	//data
	union {
		struct {
			float x, y, z;
		};
		float v[3]{ 0.0f };
	};

};

inline Vec3 operator -(const float& a, const Vec3& b) {
	return Vec3(a - b.x, a - b.y, a - b.z);
}

inline Vec3 operator +(const float& a, const Vec3& b) {
	return Vec3(a + b.x, a + b.y, a + b.z);
}

inline Vec3 operator *(const float& a, const Vec3& b) {
	return b * a;
}

inline Vec3 operator /(const float& a, const Vec3& b) {
	return Vec3(a / b.x, a / b.y, a / b.z);
}

//Negate
inline Vec3 operator -(const Vec3& a) {
	return Vec3(-a.x, -a.y, -a.z);
}

inline std::ostream& operator <<(std::ostream& os, const Vec3& a) {
	return os << "Vector3" << '(' << a.x << ',' << a.y << ',' << a.z << ')';
}

using Color = Vec3;

#endif // !VEC3_H_

