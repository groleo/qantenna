/*
 * Copyright (C) 2006 by Pablo Odorico <pablo.odorico@gmail.com>
 * Under the GPLv2, read LICENCE
 */

#include "vec3.h"

// Constructores
Vec3::Vec3(void) {
	set(0, 0, 0);
}

Vec3::Vec3(const float &x, const float &y, const float &z) {
	set(x, y, z);
}

Vec3::Vec3(const Vec3 &v) {
	set(v.x, v.y, v.z);
}

Vec3::Vec3(const float v[3]) {
	set(v[0], v[1], v[2]);
}

Vec3::Vec3(const QVector<float> &v) {
	if(v.count()<3) return;
	set(v[0], v[1], v[2]);
}

// Destructor
Vec3::~Vec3(void) {
}

// Operadores
Vec3 & Vec3::operator= (const Vec3 &v) {
	set(v.x, v.y, v.z);
	return *this;
}

float & Vec3::operator[](int i) {
	if(i==0)
		return x;
	else if(i==1)
		return y;
	else
		return z;
}

float Vec3::operator[](int i) const {
	if(i==0)
		return x;
	else if(i==1)
		return y;
	else
		return z;
}

Vec3 & Vec3::operator+=(const Vec3 &v) {
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vec3 & Vec3::operator-=(const Vec3 &v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vec3 & 	Vec3::operator*=(float k) {
	x *= k;
	y *= k;
	z *= k;

	return *this;
}

Vec3 & Vec3::operator/=(float k) {
	x /= k;
	y /= k;
	z /= k;

	return *this;
}

Vec3 Vec3::operator+(const Vec3 &v) const {
	return Vec3(x+v.x, y+v.y, z+v.z);
}

Vec3 Vec3::operator-(const Vec3 &v) const {
	return Vec3(x-v.x, y-v.y, z-v.z);
}

Vec3 Vec3::operator*(float k) const {
	return Vec3(k*x, k*y, k*z);
}

Vec3 Vec3::operator/(float k) const {
	return Vec3(x/k, y/k, z/k);
}

Vec3 Vec3::operator-(void) const {
	return Vec3(-x, -y, -z);
}

bool Vec3::operator==(const Vec3 &v) const {
	return (x==v.x && y==v.y && z==v.z);
}

bool Vec3::operator!=(const Vec3 &v) const {
	return (x!=v.x || y!=v.y || z!=v.z);
}

// Funciones varias
float Vec3::lenght(void) const {
	return sqrt(Math::pow2(x) + Math::pow2(y) + Math::pow2(z));
}

Vec3 Vec3::normalize(void) {
	float len= lenght();
	if(len)
		return Vec3(x/len, y/len, z/len);
	else
		return Vec3(0,0,0);
}

void Vec3::set(const float &nx, const float &ny, const float &nz) {
	x= nx;
	y= ny;
	z= nz;
}

void Vec3::set(const float &val) {
	set(val, val, val);
}

void Vec3::print(void) {
	printf("(%.3f, %.3f, %.3f)", x, y, z);
}

QVector<float> Vec3::toQVector()
{
	QVector<float> vec(3);
	vec[0]= x;
	vec[1]= y;
	vec[2]= z;
	return vec;
}
