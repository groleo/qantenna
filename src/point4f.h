/***************************************************************************
 *   Copyright (C) 2007 by Lisandro Damián Nicanor Pérez Meyer             *
 *   perezmeyer@gmail.com                                                  *
 *   This code is mostly based on the code for QPointF of the sources      *
 *   of qt4-x11-4.3.2 obtained by Debian sources.                          *
 *   Parts of this code are:                                               *
 *   Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.           *
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
#ifndef POINT4F_H
#define POINT4F_H

#include <QtGlobal>

class Point4F
{
public:
	Point4F();
	Point4F(qreal xpos, qreal ypos, qreal zpos, qreal wpos = 1.0);
	Point4F(const Point4F &p);

	bool isNull() const;

	qreal x() const;
	qreal y() const;
	qreal z() const;
	qreal w() const;
	void setX(qreal x);
	void setY(qreal y);
	void setZ(qreal z);
	void setW(qreal w);

	qreal & rx();
	qreal & ry();
	qreal & rz();
	qreal & rw();

	Point4F &operator+=(const Point4F &p);
	Point4F &operator-=(const Point4F &p);
	Point4F &operator*=(qreal c);
	Point4F &operator/=(qreal c);

	friend inline bool operator==(const Point4F &, const Point4F &);
	friend inline bool operator!=(const Point4F &, const Point4F &);
	friend inline const Point4F operator+(const Point4F &, const Point4F &);
	friend inline const Point4F operator-(const Point4F &, const Point4F &);
	friend inline const Point4F operator*(qreal, const Point4F &);
	friend inline const Point4F operator*(const Point4F &, qreal);
	friend inline const Point4F operator-(const Point4F &);
	friend inline const Point4F operator/(const Point4F &, qreal);

	Point4F toPoint() const;

private:
	friend class QMatrix;
	friend class QTransform;

	qreal xp;
	qreal yp;
	qreal zp;
	qreal wp;
};

Q_DECLARE_TYPEINFO(Point4F, Q_MOVABLE_TYPE);

/*****************************************************************************
  Point4F stream functions
 *****************************************************************************/
#ifndef QT_NO_DATASTREAM
Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const Point4F &);
Q_CORE_EXPORT QDataStream &operator>>(QDataStream &, Point4F &);
#endif

/*****************************************************************************
  Point4F inline functions
 *****************************************************************************/

inline Point4F::Point4F() : xp(0.0), yp(0.0), zp(0.0), wp(1.0) { }

inline Point4F::Point4F(qreal xpos, qreal ypos, qreal zpos, qreal wpos) :
                xp(xpos), yp(ypos), zp(zpos), wp(wpos) { }

inline Point4F::Point4F(const Point4F &p) : xp(p.x()), yp(p.y()),
                                            zp(p.z()), wp(p.w()) { }

inline bool Point4F::isNull() const
{
	return qIsNull(xp) && qIsNull(yp) && qIsNull(zp) && qIsNull(wp);
}

inline qreal Point4F::x() const
{
	return xp;
}

inline qreal Point4F::y() const
{
	return yp;
}

inline qreal Point4F::z() const
{
	return zp;
}

inline qreal Point4F::w() const
{
	return wp;
}

inline void Point4F::setX(qreal xpos)
{
	xp = xpos;
}

inline void Point4F::setY(qreal ypos)
{
	yp = ypos;
}

inline void Point4F::setZ(qreal zpos)
{
	zp = zpos;
}

inline void Point4F::setW(qreal wpos)
{
	wp = wpos;
}

inline qreal &Point4F::rx()
{
	return xp;
}

inline qreal &Point4F::ry()
{
	return yp;
}

inline qreal &Point4F::rz()
{
	return zp;
}

inline qreal &Point4F::rw()
{
	return wp;
}

inline Point4F &Point4F::operator+=(const Point4F &p)
{
	xp+=p.xp;
	yp+=p.yp;
	zp+=p.zp;
	wp+=p.wp;
	return *this;
}

inline Point4F &Point4F::operator-=(const Point4F &p)
{
	xp-=p.xp;
	yp-=p.yp;
	zp-=p.zp;
	wp-=p.wp;
	return *this;
}

inline Point4F &Point4F::operator*=(qreal c)
{
	xp*=c;
	yp*=c;
	zp*=c;
	wp*=c;
	return *this;
}

inline bool operator==(const Point4F &p1, const Point4F &p2)
{
	return qFuzzyCompare(p1.xp, p2.xp) &&
	       qFuzzyCompare(p1.yp, p2.yp) &&
	       qFuzzyCompare(p1.zp, p2.zp) &&
	       qFuzzyCompare(p1.wp, p2.wp);
}

inline bool operator!=(const Point4F &p1, const Point4F &p2)
{
	return !qFuzzyCompare(p1.xp, p2.xp) ||
	       !qFuzzyCompare(p1.yp, p2.yp) ||
	       !qFuzzyCompare(p1.zp, p2.zp) ||
	       !qFuzzyCompare(p1.wp, p2.wp);
}

inline const Point4F operator+(const Point4F &p1, const Point4F &p2)
{
	return Point4F(p1.xp+p2.xp, p1.yp+p2.yp, p1.zp+p2.zp, p1.wp+p2.wp);
}

inline const Point4F operator-(const Point4F &p1, const Point4F &p2)
{
	return Point4F(p1.xp-p2.xp, p1.yp-p2.yp, p1.zp-p2.zp, p1.wp-p2.wp);
}

inline const Point4F operator*(const Point4F &p, qreal c)
{
	return Point4F(p.xp*c, p.yp*c, p.zp*c, p.wp*c);
}

inline const Point4F operator*(qreal c, const Point4F &p)
{
    return Point4F(p.xp*c, p.yp*c, p.zp*c, p.wp*c);
}

inline const Point4F operator-(const Point4F &p)
{
    return Point4F(-p.xp, -p.yp, -p.zp, -p.wp);
}

inline Point4F &Point4F::operator/=(qreal c)
{
	Q_ASSERT(!qFuzzyCompare(c, 0));
	xp/=c;
	yp/=c;
	zp/=c;
	wp/=c;
	return *this;
}

inline const Point4F operator/(const Point4F &p, qreal c)
{
    Q_ASSERT(!qFuzzyCompare(c, 0));
    return Point4F(p.xp/c, p.yp/c, p.zp/c, p.wp/c);
}

inline Point4F Point4F::toPoint() const
{
    return Point4F(qRound(xp), qRound(yp), qRound(zp), qRound(wp));
}

#ifndef QT_NO_DEBUG_STREAM
Q_CORE_EXPORT QDebug operator<<(QDebug d, const Point4F &p);
#endif

QT_END_HEADER

#endif // Point4F

