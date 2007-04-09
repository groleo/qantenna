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
 *   but WITHOUT ANY WARRATLY; without even the implied warranty of        *
 *   MERCHATLABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "tlcard.h"

TLCard::TLCard(int theTagNumber, int theEqualToM)
{
	tagNumber = theTagNumber;
	equalToM = theEqualToM;
	cardType = "TL";
}

TLCard::TLCard(int theTagNumber, int theEqualToM, int theTagNumber2,
               int theEqualToN, double theCharacteristicImpedance, double theLenght,
               double theRealAdmittancePort1, double theImaginaryAdmittancePort1,
               double theRealAdmittancePort2, double theImaginaryAdmittancePort2)
{
	tagNumber = theTagNumber;
	equalToM = theEqualToM;
	tagNumber2 = theTagNumber2;
	equalToN = theEqualToN;
	characteristicImpedance = theCharacteristicImpedance;
	lenght = theLenght;
	realAdmittancePort1 = theRealAdmittancePort1;
	imaginaryAdmittancePort1 = theImaginaryAdmittancePort1;
	realAdmittancePort2 = theRealAdmittancePort2;
	imaginaryAdmittancePort2 = theImaginaryAdmittancePort2;
	cardType = "TL";
}

int TLCard::getTagNumber() const
{
	return tagNumber;
}

int TLCard::getEqualToM() const
{
	return equalToM;
}

int TLCard::getTagNumber2() const
{
	return tagNumber2;
}

int TLCard::getEqualToN() const
{
	return equalToN;
}

double TLCard::getCharacteristicImpedance() const
{
	return characteristicImpedance;
}

double TLCard::getLenght() const
{
	return lenght;
}

double TLCard::getRealAdmittancePort1() const
{
	return realAdmittancePort1;
}

double TLCard::getImaginaryAdmittancePort1() const
{
	return imaginaryAdmittancePort1;
}

double TLCard::getRealAdmittancePort2() const
{
	return realAdmittancePort2;
}

double TLCard::getImaginaryAdmittancePort2() const
{
	return imaginaryAdmittancePort2;
}

QString TLCard::getCard()
{
	QString card = cardType;
	card.append(QString(" %1 %2").arg(tagNumber).arg(equalToM));
	if(equalToM == -1)
		return card + "\n";
	card.append(QString(" %1 %2 %3 %4 %5 %6 %7 %8\n")
	            .arg(tagNumber2)
	            .arg(equalToN)
	            .arg(characteristicImpedance,0,'f',6)
	            .arg(lenght,0,'f',6)
	            .arg(realAdmittancePort1,0,'f',6)
	            .arg(imaginaryAdmittancePort1,0,'f',6)
	            .arg(realAdmittancePort2,0,'f',6)
	            .arg(imaginaryAdmittancePort2,0,'f',6));
	return card;
}




