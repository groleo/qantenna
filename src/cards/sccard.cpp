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

#include "sccard.h"

SCCard::SCCard(int thePatchShape, double theXCoordinateCorner3,
               double theYCoordinateCorner3, double theZCoordinateCorner3)
{
	patchShape = thePatchShape;
	xCoordinateCorner3 = theXCoordinateCorner3;
	yCoordinateCorner3 = theYCoordinateCorner3;
	zCoordinateCorner3 = theZCoordinateCorner3;
	patchShape = true;
	fourCorners = false;
	cardType = "SC";
}

SCCard::SCCard(double theXCoordinateCorner3, double theYCoordinateCorner3,
               double theZCoordinateCorner3)
{
	xCoordinateCorner3 = theXCoordinateCorner3;
	yCoordinateCorner3 = theYCoordinateCorner3;
	zCoordinateCorner3 = theZCoordinateCorner3;
	patchShape = false;
	fourCorners = false;
	cardType = "SC";
}

SCCard::SCCard(int thePatchShape, double theXCoordinateCorner3,
               double theYCoordinateCorner3, double theZCoordinateCorner3,
               double theXCoordinateCorner4, double theYCoordinateCorner4,
               double theZCoordinateCorner4)
{
	patchShape = thePatchShape;
	xCoordinateCorner3 = theXCoordinateCorner3;
	yCoordinateCorner3 = theYCoordinateCorner3;
	zCoordinateCorner3 = theZCoordinateCorner3;
	xCoordinateCorner4 = theXCoordinateCorner4;
	yCoordinateCorner4 = theYCoordinateCorner4;
	zCoordinateCorner4 = theZCoordinateCorner4;
	patchShape = true;
	fourCorners = true;
	cardType = "SC";
}

bool SCCard::getPatchShapeExists() const
{
	return patchShapeExists;
}

bool SCCard::getFourCorners() const
{
	return fourCorners;
}

int SCCard::getPatchShape() const
{
	return patchShape;
}

double SCCard::getXCoordinateCorner3() const
{
	return xCoordinateCorner3;
}

double SCCard::getYCoordinateCorner3() const
{
	return yCoordinateCorner3;
}

double SCCard::getZCoordinateCorner3() const
{
	return zCoordinateCorner3;
}


double SCCard::getXCoordinateCorner4() const
{
	return xCoordinateCorner4;
}

double SCCard::getYCoordinateCorner4() const
{
	return yCoordinateCorner4;
}

double SCCard::getZCoordinateCorner4() const
{
	return zCoordinateCorner4;
}

QString SCCard::getCard()
{
	/// FIXME read NEC2++ doc and re write this card
	QString card = cardType;

	if(patchShapeExists)
		card.append(QString(" %1 %2").arg(patchShape).arg(xCoordinateCorner3,0,'f',6));
	else
		card.append(QString(" 0 %1").arg(xCoordinateCorner3,0,'f',6));

	card.append(QString(" %1 %2").arg(yCoordinateCorner3,0,'f',6).arg(zCoordinateCorner3,0,'f',6));
	if(fourCorners)
		card.append(QString(" %1 %2 %3")
		            .arg(xCoordinateCorner4,0,'f',6)
		            .arg(yCoordinateCorner4,0,'f',6)
		            .arg(zCoordinateCorner4,0,'f',6));
	card.append("\n");
	return card;
}
