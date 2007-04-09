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

#include "spcard.h"

SPCard::SPCard(int thePatchShape, double theXCoordinateCorner1,
               double theYCoordinateCorner1, double theZCoordinateCorner1,
               double theXCoordinateCorner2, double theYCoordinateCorner2,
               double theZCoordinateCorner2 )
{
	patchShape = thePatchShape;
	xCoordinateCorner1 = theXCoordinateCorner1;
	yCoordinateCorner1 = theYCoordinateCorner1;
	zCoordinateCorner1 = theZCoordinateCorner1;
	xCoordinateCorner2 = theXCoordinateCorner2;
	yCoordinateCorner2 = theYCoordinateCorner2;
	zCoordinateCorner2 = theZCoordinateCorner2;
	cardType = "SP";
}

int SPCard::getPatchShape() const
{
	return patchShape;
}

double SPCard::getXCoordinateCorner1() const
{
	return xCoordinateCorner1;
}

double SPCard::getYCoordinateCorner1() const
{
	return yCoordinateCorner1;
}

double SPCard::getZCoordinateCorner1() const
{
	return zCoordinateCorner1;
}

double SPCard::getXCoordinateCorner2() const
{
	return xCoordinateCorner2;
}

double SPCard::getYCoordinateCorner2() const
{
	return yCoordinateCorner2;
}

double SPCard::getZCoordinateCorner2() const
{
	return zCoordinateCorner2;
}

QString SPCard::getCard()
{
	return cardType + QString(" %1 0 %2 %3 %4 %5 %6 %7\n")
	       .arg(patchShape)
	       .arg(xCoordinateCorner1,0,'f',6)
	       .arg(yCoordinateCorner1,0,'f',6)
	       .arg(zCoordinateCorner1,0,'f',6)
	       .arg(xCoordinateCorner2,0,'f',6)
	       .arg(yCoordinateCorner2,0,'f',6)
	       .arg(zCoordinateCorner2,0,'f',6);
}


