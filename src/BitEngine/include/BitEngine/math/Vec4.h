#pragma once

#include <math.h>

namespace be::math {

struct Vec4 {
	Vec4 operator+(const Vec4 &other) const;
	Vec4 operator+=(const Vec4 &other);

	Vec4 operator-(const Vec4 &other)const;
	Vec4 operator-=(const Vec4 &other);

	Vec4 operator*(float scalar) const;
	Vec4 operator*=(float scalar);

	Vec4 operator/(float scalar) const;
	Vec4 operator/=(float scalar);

	float x { 0.0f };
	float y { 0.0f };
	float z { 0.0f };
	float w { 0.0f };
};

}
