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

#include "nenhcards.h"

NENHCards::NENHCards(bool isItNECard, int theCoordinateSystemType,
										 int theNumberOfPointsXR, int theNumberOfPointsYPhi,
										 int theNumberOfPointsZTheta, double theCoordinateXR,
										 double theCoordinateYPhi, double theCoordinateZTheta,
										 double theIncrementXR, double theIncrementYPhi,
										 double theIncrementZTheta)
{
	isNECard = isItNECard;
	coordinateSystemType = theCoordinateSystemType;
	numberOfPointsXR = theNumberOfPointsXR;
	numberOfPointsYPhi = theNumberOfPointsYPhi;
	numberOfPointsZTheta = theNumberOfPointsZTheta;
	coordinateXR = theCoordinateXR;
	coordinateYPhi = theCoordinateYPhi;
	coordinateZTheta = theCoordinateZTheta;
	incrementXR = theIncrementXR;
	incrementYPhi = theIncrementYPhi;
	incrementZTheta = theIncrementZTheta;
	if(isNECard)
		cardType = "NE";
	else
		cardType = "NH";
}

bool NENHCards::getIsNECard() const
{
	return isNECard;
}

int NENHCards::getCoordinateSystemType() const
{
	return coordinateSystemType;
}

int NENHCards::getNumberOfPointsXR() const
{
	return numberOfPointsXR;
}

int NENHCards::getNumberOfPointsYPhi() const
{
	return numberOfPointsYPhi;
}

int NENHCards::getNumberOfPointsZTheta() const
{
	return numberOfPointsZTheta;
}

double NENHCards::getCoordinateXR() const
{
	return coordinateXR;
}

double NENHCards::getCoordinateYPhi() const
{
	return coordinateYPhi;
}

double NENHCards::getCoordinateZTheta() const
{
	return coordinateZTheta;
}

double NENHCards::getIncrementXR() const
{
	return incrementXR;
}

double NENHCards::getIncrementYPhi() const
{
	return incrementYPhi;
}

double NENHCards::getIncrementZTheta() const
{
	return incrementZTheta;
}

QString NENHCards::getCard()
{
	return cardType + QString(" %1 %2 %3 %4 %5 %6 %7 %8 %9 %10\n")
	       .arg(coordinateSystemType)
	       .arg(numberOfPointsXR)
	       .arg(numberOfPointsYPhi)
	       .arg(numberOfPointsZTheta)
	       .arg(coordinateXR,0,'f',6)
	       .arg(coordinateYPhi,0,'f',6)
	       .arg(coordinateZTheta,0,'f',6)
	       .arg(incrementXR,0,'f',6)
	       .arg(incrementYPhi,0,'f',6)
	       .arg(incrementZTheta,0,'f',6);
}





