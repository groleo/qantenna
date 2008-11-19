/***************************************************************************
 *   Copyright (C) 2006 by Pablo Odorico                                   *
 *   pablo.odorico@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cstdio>
#include <math.h>
#include <QVector>

#include "mmath.h"

using namespace std;

//! 3d Vector
class Vec3 {

public:
	Vec3(void);
	Vec3(const float &x, const float &y, const float &z);
	Vec3(const Vec3 &v);
	Vec3(const float v[3]);
	Vec3(const QVector<float> &v);
	~Vec3(void);

	Vec3 & operator= (const Vec3 &v);
	float & operator[](int i);
	float	operator[](int i) const;
	Vec3 &	operator+=(const Vec3 &v);
	Vec3 &	operator-=(const Vec3 &v);
	Vec3 & 	operator*=(float k);
	Vec3 & 	operator/=(float k);
	Vec3 	operator+(const Vec3 &v) const;
	Vec3 	operator-(const Vec3 &v) const;
	Vec3 	operator*(float k) const;
	Vec3 	operator/(float k) const;
	Vec3 	operator-(void) const;
	bool	operator==(const Vec3 &v) const;
	bool	operator!=(const Vec3 &v) const;

	float lenght(void) const;
	Vec3 normalize(void);

	void set(const float &nx, const float &ny, const float &nz);
	void set(const float &val);
	void print(void);

	QVector<float> toQVector();

	float x, y, z;
};

#endif
