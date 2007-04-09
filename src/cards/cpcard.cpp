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

#include "cpcard.h"

CPCard::CPCard(int theTag1, int theSegmentNumber1,
               int theTag2, int theSegmentNumber2)
{
	tag1 = theTag1;
	segmentNumber1 = theSegmentNumber1;
	tag2 = theTag2;
	segmentNumber2 = theSegmentNumber2;
	if(segmentNumber1 < 0)
		secondParameter = false;
	else
		secondParameter = true;
	cardType = "CP";
}

bool CPCard::getSecondParameter() const
{
	return secondParameter;
}

int CPCard::getTag1() const
{
	return tag1;
}

int CPCard::getSegmentNumber1() const
{
	return segmentNumber1;
}

int CPCard::getTag2() const
{
	return tag2;
}

int CPCard::getSegmentNumber2() const
{
	return segmentNumber2;
}

QString CPCard::getCard()
{
	QString card = cardType;
	card.append(QString("%1 %2").arg(tag1).arg(segmentNumber1));
	if(secondParameter)
		card.append(QString("%1 %2").arg(tag2).arg(segmentNumber2));
	card.append("\n");
	return card;
}

