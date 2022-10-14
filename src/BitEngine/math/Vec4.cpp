#include "math/Vec4.h"

namespace be::math {

Vec4 Vec4::operator+(const Vec4 &other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
Vec4 Vec4::operator+=(const Vec4 &other) { return *this = { x + other.x, y + other.y, z + other.z, w + other.w }; }

Vec4 Vec4::operator-(const Vec4 &other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
Vec4 Vec4::operator-=(const Vec4 &other) { return *this = { x - other.x, y - other.y, z - other.z, w - other.w }; }

Vec4 Vec4::operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
Vec4 Vec4::operator*=(float scalar) { return *this = { x * scalar, y * scalar, z * scalar , w * scalar}; }

Vec4 Vec4::operator/(float scalar) const { return { x / scalar, y / scalar, z / scalar, w / scalar }; }
Vec4 Vec4::operator/=(float scalar) { return *this = { x / scalar, y / scalar, z / scalar, w / scalar }; }

}
