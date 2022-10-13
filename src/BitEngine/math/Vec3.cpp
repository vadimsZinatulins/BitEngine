#include "math/Vec3.h"

namespace be::math {

Vec3 Vec3::operator+(const Vec3 &other) const { return { x + other.x, y + other.y, z + other.z }; }
Vec3 Vec3::operator+=(const Vec3 &other) { return *this = { x + other.x, y + other.y, z + other.z }; }

Vec3 Vec3::operator-(const Vec3 &other) const { return { x - other.x, y - other.y, z - other.z }; }
Vec3 Vec3::operator-=(const Vec3 &other) { return *this = { x - other.x, y - other.y, z - other.z }; }

Vec3 Vec3::operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
Vec3 Vec3::operator*=(float scalar) { return *this = { x * scalar, y * scalar, z * scalar }; }

Vec3 Vec3::operator/(float scalar) const { return { x / scalar, y / scalar, z / scalar }; }
Vec3 Vec3::operator/=(float scalar) { return *this = { x / scalar, y / scalar, z / scalar }; }

}
