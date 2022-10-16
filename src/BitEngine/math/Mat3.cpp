#include "math/Mat3.h"
#include "math/Vec3.h"

namespace be::math {

Mat3::Mat3(
	float v00, float v01, float v02,
	float v10, float v11, float v12,
	float v20, float v21, float v22
) {
	m_values[0][0] = v00;
	m_values[0][1] = v10;
	m_values[0][2] = v20;

	m_values[1][0] = v01;
	m_values[1][1] = v11;
	m_values[1][2] = v21;

	m_values[2][0] = v02;
	m_values[2][1] = v12;
	m_values[2][2] = v22;
}

float &Mat3::operator()(int row, int column) { return m_values[column][row]; }
float Mat3::operator()(int row, int column) const { return m_values[column][row]; }

Vec3 &Mat3::operator[](int column) { return *reinterpret_cast<Vec3*>(m_values[column]); }
const Vec3 &Mat3::operator[](int column) const { return *reinterpret_cast<const Vec3*>(m_values[column]); }

Mat3 Mat3::operator*(const Mat3 &other) const {
	return Mat3(
		m_values[0][0] * other.m_values[0][0] + m_values[0][1] * other.m_values[1][0] + m_values[0][2] * other.m_values[2][0],
		m_values[0][0] * other.m_values[0][1] + m_values[0][1] * other.m_values[1][1] + m_values[0][2] * other.m_values[2][1],
		m_values[0][0] * other.m_values[0][2] + m_values[0][1] * other.m_values[1][2] + m_values[0][2] * other.m_values[2][2],

		m_values[1][0] * other.m_values[0][0] + m_values[1][1] * other.m_values[1][0] + m_values[1][2] * other.m_values[2][0],
		m_values[1][0] * other.m_values[0][1] + m_values[1][1] * other.m_values[1][1] + m_values[1][2] * other.m_values[2][1],
		m_values[1][0] * other.m_values[0][2] + m_values[1][1] * other.m_values[1][2] + m_values[1][2] * other.m_values[2][2],

		m_values[2][0] * other.m_values[0][0] + m_values[2][1] * other.m_values[1][0] + m_values[2][2] * other.m_values[2][0],
		m_values[2][0] * other.m_values[0][1] + m_values[2][1] * other.m_values[1][0] + m_values[2][2] * other.m_values[2][1],
		m_values[2][0] * other.m_values[0][2] + m_values[2][2] * other.m_values[1][0] + m_values[2][2] * other.m_values[2][2]
	);
}

Vec3 Mat3::operator*(const Vec3 &other) const {
	return {
		m_values[0][0] * other.x + m_values[0][1] * other.y + m_values[0][2] * other.z,
		m_values[1][0] * other.x + m_values[1][1] * other.y + m_values[1][2] * other.z,
		m_values[2][0] * other.x + m_values[2][1] * other.y + m_values[2][2] * other.z
	};
}

Mat3 inverse(const Mat3 &matrix) {
	const auto &a { matrix[0] };
	const auto &b { matrix[1] };
	const auto &c { matrix[2] };

	auto r0 { cross(b, c) };
	auto r1 { cross(c, a) };
	auto r2 { cross(a, b) };

	auto invDet { 1.0f / dot(r2, c) };

	return Mat3(
		r0.x * invDet, r0.y * invDet, r0.z * invDet,
		r1.x * invDet, r1.y * invDet, r1.z * invDet,
		r2.x * invDet, r2.y * invDet, r2.z * invDet
	);
}

Mat3 rotationMatX(float t) {
	auto c { std::cos(t) };
	auto s { std::sin(t) };

	return Mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, c, -s,
		0.0f, s, c
	);
}

Mat3 rotationMatY(float t) {
	auto c { std::cos(t) };
	auto s { std::sin(t) };

	return Mat3(
		c, 0.0f, s,
		0.0f, 1.0f, 0.0f,
		-s, 0.0f, c
	);
}

Mat3 rotationMatZ(float t) {
	auto c { std::cos(t) };
	auto s { std::sin(t) };

	return Mat3(
		c, -s, 0.0f,
		s, c, 0.0f,
		0.0f, 0.0f, 1.0
	);
}

Mat3 rotationMat(float t, const Vec3 &vector) {
	auto c { std::cos(t) };
	auto s { std::sin(t) };
	auto d { 1.0f - c };

	auto x { vector.x * d };
	auto y { vector.y * d };
	auto z { vector.z * d };

	auto axay { x * vector.y };
	auto axaz { x * vector.z };
	auto ayaz { y * vector.z };

	return Mat3(
		c + x * vector.x, axay - s * vector.z, axaz + s * vector.y,
		axay + s * vector.z, c + y * vector.y, ayaz - s * vector.x,
		axaz - s * vector.y, ayaz + s * vector.x, c + z * vector.z
	);
}

}
