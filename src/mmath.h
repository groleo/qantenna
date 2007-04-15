#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "vec3.h"

// This file is used by and uses Vec3
class Vec3;

namespace Math {


	float rad2deg(const float &angle);
	float deg2rad(const float &angle);
	float pow2(const float &val);

	float SIN(const float &ang);
	float COS(const float &ang);
	float TAN(const float &ang);

	float ASIN(const float &val);
	float ACOS(const float &val);
	float ATAN(const float &val);
	float ATAN2(const float &val1, const float &val2);

	Vec3 getCartesian(const float &rho, const float &phi, const float &theta);

	Vec3 triangleNormal(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);
	Vec3 quadNormal(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, const Vec3 &v4);

    float dot(const Vec3 &v1, const Vec3 &v2);
	Vec3 cross(const Vec3 &v1, const Vec3 &v2);

	Vec3 mix(const Vec3 &v1, const Vec3 &v2, const float &porc);
};

#endif // MATH_H
