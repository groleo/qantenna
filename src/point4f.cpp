/***************************************************************************
 *   Copyright (C) 2007 by Lisandro DamiÃ¡n Nicanor PÃ©rez Meyer             *
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
#include <QDebug>

#include "point4f.h"

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const Point4F &p)
{
    d << "Point4F(" << p.x() << ", " << p.y() <<
         ", " << p.z() << ", " << p.w() << ")";
    return d;
}
#endif

/*!
    \class Point4F
    \ingroup multimedia

    \brief The Point4F class defines a point in the plane using
    floating point precision.
*/

#ifndef QT_NO_DATASTREAM

QDataStream &operator<<(QDataStream &s, const Point4F &p)
{
    s << double(p.x()) << double(p.y()) << double(p.z()) << double(p.w());
    return s;
}

QDataStream &operator>>(QDataStream &s, Point4F &p)
{
	double x, y, z, w;
	s >> x;
	s >> y;
	s >> z;
	s >> w;
	p.setX(qreal(x));
	p.setY(qreal(y));
	p.setZ(qreal(z));
	p.setW(qreal(w));
	return s;
}
#endif // QT_NO_DATASTREAM
