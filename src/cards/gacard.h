/***************************************************************************
 *   Copyright (C) 2007 by                                                 *
 *   Lisandro Damián Nicanor Pérez Meyer - perezmeyer en/at gmail.com      *
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

#ifndef GACARD_H
#define GACARD_H

#include "genericcard.h"
#include <QString>

/** GA card: Wire arc specification */

class GACard : public GenericCard
{
public:
	GACard(int theTagNumber, int theNumberOfSegments, double theArcRadius,
	       double theFirstEndAngle, double theSecondEndAngle,
	       double theWireRadius);

	int getTagNumber() const;
	int getNumberOfSegments() const;
	double getArcRadius() const;
	double getFirstEndAngle() const;
	double getSecondEndAngle() const;
	double getWireRadius() const;

	QString getCard();

private:
	/// Tag number assigned to all segments of the wire arc.
	int tagNumber;
	/// Number of segments into which the arc will be divided.
	int numberOfSegments;
	/// Arc radius (center is the origin and the axis is the y axis).
	double arcRadius;
	/**
		Angle of first end of the arc measured from the x axis in a left-hand
		direction about the y axis (degrees).
	*/
	double firstEndAngle;
	/// Angle of the second end of the arc.
	double secondEndAngle;
	/// Wire radius.
	double wireRadius;

};

#endif // GACARD_H
