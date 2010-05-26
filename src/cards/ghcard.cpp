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

#include "ghcard.h"

GHCard::GHCard(int theTagNumber, int theNumberOfSegments,
               double theSpacingBetweenTurns, double theTotalLenght,
               double theRadiusXZ0, double theRadiusYZ0,
               double theRadiusXZTotalLenght, double theRadiusYZTotalLenght,
               double theRadiusOfWire)
{
	tagNumber = theTagNumber;
	numberOfSegments = theNumberOfSegments;
	spacingBetweenTurns = theSpacingBetweenTurns;
	totalLenght = theTotalLenght;
	radiusXZ0 = theRadiusXZ0;
	radiusYZ0 = theRadiusYZ0;
	radiusXZTotalLenght = theRadiusXZTotalLenght;
	radiusYZTotalLenght = theRadiusYZTotalLenght;
	radiusOfWire = theRadiusOfWire;
	cardType = "GH";
}

int GHCard::getTagNumber() const
{
	return tagNumber;
}

int GHCard::getNumberOfSegments() const
{
	return numberOfSegments;
}

double GHCard::getSpacingBetweenTurns() const
{
	return spacingBetweenTurns;
}

double GHCard::getTotalLenght() const
{
	return totalLenght;
}

double GHCard::getRadiusXZ0() const
{
	return radiusXZ0;
}

double GHCard::getRadiusYZ0() const
{
	return radiusYZ0;
}

double GHCard::getRadiusXZTotalLenght() const
{
	return radiusXZTotalLenght;
}

double GHCard::getRadiusYZTotalLenght() const
{
	return radiusYZTotalLenght;
}

double GHCard::getRadiusOfWire() const
{
	return radiusOfWire;
}

QString GHCard::getCard()
{
	return cardType + QString(" %1 %2 %3 %4 %5 %6 %7 %8 %9\n")
	       .arg(tagNumber)
	       .arg(numberOfSegments)
	       .arg(spacingBetweenTurns,0,'f',6)
	       .arg(totalLenght,0,'f',6)
	       .arg(radiusXZ0,0,'f',6)
	       .arg(radiusYZ0,0,'f',6)
	       .arg(radiusXZTotalLenght,0,'f',6)
	       .arg(radiusYZTotalLenght,0,'f',6)
	       .arg(radiusOfWire,0,'f',6);
}





