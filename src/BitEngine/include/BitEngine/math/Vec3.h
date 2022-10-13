#pragma once

#include <cmath>
#include <math.h>

namespace be::math {

struct Vec3 {
	Vec3 operator+(const Vec3 &other) const;
	Vec3 operator+=(const Vec3 &other);

	Vec3 operator-(const Vec3 &other)const;
	Vec3 operator-=(const Vec3 &other);

	Vec3 operator*(float scalar) const;
	Vec3 operator*=(float scalar);

	Vec3 operator/(float scalar) const;
	Vec3 operator/=(float scalar);

	float x { 0.0f };
	float y { 0.0f };
	float z { 0.0f };
};

inline float length(const Vec3 &vector) { return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z); }

inline Vec3 normalized(const Vec3 &vector) { return vector / length(vector); }

inline float dot(const Vec3 &a, const Vec3 &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

inline Vec3 cross(const Vec3 &a, const Vec3 &b) { 
	return { 
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x 
	}; 
}

inline Vec3 project(const Vec3 &a, const Vec3 &b) { return b * (dot(a, b) / dot(b, b)); }

inline Vec3 reject(const Vec3 &a, const Vec3 &b) { return a - project(a, b); }

}
