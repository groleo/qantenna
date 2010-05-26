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

#include "ldcard.h"

LDCard::LDCard(int theLoadType)
{
	loadType = theLoadType;
	shortAllLoads = true;
	cardType = "LD";
}

LDCard::LDCard(int theLoadType, int theTagNumber, int theEqualToM, int theEqualToN,
               double theResistance, double theInductance, double theCapacitance)
{
	loadType = theLoadType;
	tagNumber = theTagNumber;
	equalToM = theEqualToM;
	equalToN = theEqualToN;
	resistance = theResistance;
	inductance = theInductance;
	capacitance = theCapacitance;
	shortAllLoads = false;
	cardType = "LD";
}

LDCard::LDCard(int theLoadType, int theTagNumber, int theEqualToM, int theEqualToN,
               double theResistance, double theReactance)
{
	loadType = theLoadType;
	tagNumber = theTagNumber;
	equalToM = theEqualToM;
	equalToN = theEqualToN;
	resistance = theResistance;
	inductance = theReactance;
	shortAllLoads = false;
	cardType = "LD";
}

LDCard::LDCard(int theLoadType, int theTagNumber, int theEqualToM, int theEqualToN,
               double theConductivity)
{
	loadType = theLoadType;
	tagNumber = theTagNumber;
	equalToM = theEqualToM;
	equalToN = theEqualToN;
	resistance = theConductivity;
	shortAllLoads = false;
	cardType = "LD";
}

bool LDCard::getShortAllLoads() const
{
	return shortAllLoads;
}

int LDCard::getLoadType() const
{
	return loadType;
}

int LDCard::getTagNumber() const
{
	return tagNumber;
}

int LDCard::getEqualToM() const
{
	return equalToM;
}

int LDCard::getEqualToN() const
{
	return equalToN;
}

double LDCard::getResistance() const
{
	return resistance;
}

double LDCard::getInductance() const
{
	return inductance;
}

double LDCard::getCapacitance() const
{
	return capacitance;
}

QString LDCard::getCard()
{
	QString card = cardType + QString(" %1").arg(loadType);
	if(shortAllLoads)
		return card + "\n";
	card.append(QString(" %1 %2 %3 %4")
	            .arg(tagNumber)
	            .arg(equalToM)
	            .arg(equalToN)
	            .arg(resistance,0,'f',6));
	if(loadType == 5)
		return card + "\n";
	card.append(QString(" %1").arg(inductance,0,'f',6));
	if(loadType == 4)
		return card + "\n";
	card.append(QString(" %1\n").arg(capacitance,0,'f',6));

	return card;
}

