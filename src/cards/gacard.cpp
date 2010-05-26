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
 *   59 QString("%1")le Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "gacard.h"

GACard::GACard(int theTagNumber, int theNumberOfSegments, double theArcRadius,
               double theFirstEndAngle, double theSecondEndAngle,
               double theWireRadius)
{
	tagNumber = theTagNumber;
	numberOfSegments = theNumberOfSegments;
	arcRadius = theArcRadius;
	firstEndAngle = theFirstEndAngle;
	secondEndAngle = theSecondEndAngle;
	wireRadius = theWireRadius;
	cardType = "GA";
}

int GACard::getTagNumber() const
{
	return tagNumber;
}

int GACard::getNumberOfSegments() const
{
	return numberOfSegments;
}

double GACard::getArcRadius() const
{
	return arcRadius;
}

double GACard::getFirstEndAngle() const
{
	return firstEndAngle;
}

double GACard::getSecondEndAngle() const
{
	return secondEndAngle;
}

double GACard::getWireRadius() const
{
	return wireRadius;
}

QString GACard::getCard()
{
	return cardType + QString(" %1 %2 %3 %4 %5 %6\n")
	       .arg(tagNumber)
	       .arg(numberOfSegments)
	       .arg(arcRadius,0,'f',6)
	       .arg(firstEndAngle,0,'f',6)
	       .arg(secondEndAngle,0,'f',6)
	       .arg(arcRadius,0,'f',6);
}






