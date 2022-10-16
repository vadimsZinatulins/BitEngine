#pragma once 

#include <math.h>

namespace be::math {

struct Vec3;

class Mat3 {
public:
	Mat3() = default;
	~Mat3() = default;

	Mat3(
		float v00, float v01, float v02,
		float v10, float v11, float v12,
		float v20, float v21, float v22
	);

	float &operator()(int row, int column);
	float operator()(int row, int column) const;

	Vec3 &operator[](int column);
	const Vec3 &operator[](int column) const;

	Mat3 operator *(const Mat3 &other) const;

	Vec3 operator*(const Vec3 &other) const;
private:
	float m_values[3][3];
};

Mat3 inverse(const Mat3 &matrix);
Mat3 rotationMatX(float t);
Mat3 rotationMatY(float t);
Mat3 rotationMatZ(float t);
Mat3 rotationMat(float t, const Vec3 &vector);

}
