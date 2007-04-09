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

#include "frcard.h"

FRCard::FRCard(int theTypeOfStepping, int theNumberOfFrequencySteps,
               double theFrequency, double theFrequencyIncrement)
{
	typeOfStepping = theTypeOfStepping;
	numberOfFrequencySteps = theNumberOfFrequencySteps;
	frequency = theFrequency;
	frequencyIncrement = theFrequencyIncrement;
	cardType = "FR";

	/**
		Note: for the special case of QAntenna (at the time of version 0.1 to version
		0.2), the number of frequency steps and the frequency increment would be set
		to 1 and 0 in the constructor, as only one radiation pattern is
		considered.
	*/
	numberOfFrequencySteps = 1;
	frequencyIncrement = 0;
}


int FRCard::getTypeOfStepping() const
{
	return typeOfStepping;
}

int FRCard::getNumberOfFrequencySteps() const
{
	return numberOfFrequencySteps;
}

double FRCard::getFrequency() const
{
	return frequency;
}

double FRCard::getFrequencyIncrement() const
{
	return frequencyIncrement;
}

void FRCard::setTypeOfStepping(int theTypeOfStepping)
{
	typeOfStepping = theTypeOfStepping;
}

void FRCard::setNumberOfFrequencySteps(int theNumberOfFrequencySteps)
{
	numberOfFrequencySteps = theNumberOfFrequencySteps;
}

void FRCard::setFrequency(double theFrequency)
{
	frequency = theFrequency;
}

void FRCard::setFrequencyIncrement(double theFrequencyIncrement)
{
	frequencyIncrement = theFrequencyIncrement;
}

QString FRCard::getCard()
{
	return cardType + QString(" %1 %2 0 0 %3 %4\n")
	       .arg(typeOfStepping)
	       .arg(numberOfFrequencySteps)
	       .arg(frequency,0,'f',6)
	       .arg(frequencyIncrement,0,'f',6);
}


