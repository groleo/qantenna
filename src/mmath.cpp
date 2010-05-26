#include "mmath.h"

namespace Math {

// Constantes
const float piDiv180= M_PI / 180.0;

float rad2deg(const float &angle)
{
	return angle * 1/piDiv180;
}

float deg2rad(const float &angle)
{
	return angle * piDiv180;
}

float pow2(const float &val)
{
	return val*val;
}

float SIN(const float &ang)
{
	return sin(ang * piDiv180);
}

float COS(const float &ang)
{
	return cos(ang * piDiv180);
}

float TAN(const float &ang)
{
	return tan(ang);
}

float ASIN(const float &val)
{
	return asin(val) / piDiv180;
}

float ACOS(const float &val)
{
	return acos(val) / piDiv180;
}

float ATAN(const float &val)
{
	return atan(val) / piDiv180;
}

float ATAN2(const float &val1, const float &val2)
{
	return atan2(val1, val2) / piDiv180;
}

Vec3 triangleNormal(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
	/*
		Counter Clock-Wise (right hand rule)
	*/
	Vec3 ret;

	ret.x = (v2.y-v1.y)*(v3.z-v1.z)-(v2.z-v1.z)*(v3.y-v1.y);
	ret.y = (v2.z-v1.z)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.z-v1.z);
	ret.z = (v2.x-v1.x)*(v3.y-v1.y)-(v2.y-v1.y)*(v3.x-v1.x);

	return ret.normalize();
}


Vec3 quadNormal(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3, const Vec3 &v4)
{
	/*
	Calculates a quad normal as an average of the triangle
	normals at the four corners
		1------4
		| ·  · |  Counter Clock-Wise (right hand rule)
		|      |
		| ·  · |
		2------3
	*/

	Vec3 ret;

	ret= triangleNormal(v1, v2, v4) + triangleNormal(v2, v3, v1) +
		 triangleNormal(v3, v4, v2) + triangleNormal(v4, v1, v3);

	return ret.normalize();
}


Vec3 getCartesian(const float &rho, const float &phi, const float &theta)
{
	return Vec3(
		rho * SIN(phi) * COS(theta),
		rho * SIN(phi) * SIN(theta),
		rho * COS(phi));
}


float dot(const Vec3 &v1, const Vec3 &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

Vec3 mix(const Vec3 &v1, const Vec3 &v2, const float &porc)
{
	// Similar to GLSL vector mix
	float porc1= 1-porc;
	return v1*porc1 + v2*porc;
}

}
