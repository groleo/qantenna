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

#include "ntcard.h"

NTCard::NTCard(int theTagNumber, int theEqualToM)
{
	tagNumber = theTagNumber;
	equalToM = theEqualToM;
	cardType = "NT";
}

NTCard::NTCard(int theTagNumber, int theEqualToM, int theTagNumber2,
               int theEqualToN, double theReal11, double theImaginary11,
               double theReal12, double theImaginary12, double theReal22,
               double theImaginary22)
{
	tagNumber = theTagNumber;
	equalToM = theEqualToM;
	tagNumber2 = theTagNumber2;
	equalToN = theEqualToN;
	real11 = theReal11;
	imaginary11 = theImaginary11;
	real12 = theReal12;
	imaginary12 = theImaginary12;
	real22 = theReal22;
	imaginary22 = theImaginary22;
	cardType = "NT";
}

int NTCard::getTagNumber() const
{
	return tagNumber;
}

int NTCard::getEqualToM() const
{
	return equalToM;
}

int NTCard::getTagNumber2() const
{
	return tagNumber2;
}

int NTCard::getEqualToN() const
{
	return equalToN;
}

double NTCard::getReal11() const
{
	return real11;
}

double NTCard::getImaginary11() const
{
	return imaginary11;
}

double NTCard::getReal12() const
{
	return real12;
}

double NTCard::getImaginary12() const
{
	return imaginary12;
}

double NTCard::getReal22() const
{
	return real22;
}

double NTCard::getImaginary22() const
{
	return imaginary22;
}

QString NTCard::getCard()
{
	QString card = cardType + QString(" %1 %2").arg(tagNumber).arg(equalToM);
	if(equalToM == -1)
		return card + "\n";
	card.append(QString(" %1 %2 %3 %4 %5 %6 %7 %8\n")
	            .arg(tagNumber2))
	            .arg(equalToN)
	            .arg(real11,0,'f',6)
	            .arg(imaginary11,0,'f',6)
	            .arg(real12,0,'f',6)
	            .arg(imaginary12,0,'f',6)
	            .arg(real22,0,'f',6)
	            .arg(imaginary22,0,'f',6);
	return card;
}



