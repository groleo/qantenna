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

#include "gmcard.h"

GMCard::GMCard(int theTagNumberIncrement, int theNumberOfNewStructures,
               double theXRotationAngle, double theYRotationAngle,
               double theZRotationAngle, double theXTranslation,
               double theYTranslation, double theZTranslation,
               double theInitialTag)
{
	tagNumberIncrement = theTagNumberIncrement;
	numberOfNewStructures = theNumberOfNewStructures;
	xRotationAngle = theXRotationAngle;
	yRotationAngle = theYRotationAngle;
	zRotationAngle = theZRotationAngle;
	xTranslation = theXTranslation;
	yTranslation = theYTranslation;
	zTranslation = theZTranslation;
	initialTag = theInitialTag;
	cardType = "GM";
}

int GMCard::getTagNumberIncrement() const
{
	return tagNumberIncrement;
}

int GMCard::getNumberOfNewStructures() const
{
	return numberOfNewStructures;
}

double GMCard::getXRotationAngle() const
{
	return xRotationAngle;
}

double GMCard::getYRotationAngle() const
{
	return yRotationAngle;
}

double GMCard::getZRotationAngle() const
{
	return zRotationAngle;
}

double GMCard::getXTranslation() const
{
	return xTranslation;
}

double GMCard::getYTranslation() const
{
	return yTranslation;
}

double GMCard::getZTranslation() const
{
	return zTranslation;
}

double GMCard::getInitialTag() const
{
	return initialTag;
}

QString GMCard::getCard()
{
	return cardType + QString(" %1 %2 %3 %4 %5 %6 %7 %8 %9\n")
	       .arg(tagNumberIncrement)
	       .arg(numberOfNewStructures)
	       .arg(xRotationAngle,0,'f',6)
	       .arg(yRotationAngle,0,'f',6)
	       .arg(zRotationAngle,0,'f',6)
	       .arg(xTranslation,0,'f',6)
	       .arg(yTranslation,0,'f',6)
	       .arg(zTranslation,0,'f',6)
	       .arg(initialTag,0,'f',6);
}



