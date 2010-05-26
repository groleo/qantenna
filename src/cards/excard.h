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

#ifndef EXCARD_H
#define EXCARD_H

#include "genericcard.h"
#include <QString>

//FIXME The description of this card should be read from NEC2++'s doc and re-written
/**
	EX card: exitation
	Specify the excitation for the structure. The excitation can be voltage
	sources on the structure, an elementary current source, or a plane-wave
	incident on the structure.
	Note from the programmer: as the fields changes their uses depending on
	the type of exitation, I did not botter to name them properly.
*/

class EXCard : public GenericCard
{
public:
	// typeOfExcitation == 0 or typeOfExcitation == 5
	EXCard(int theTypeOfExcitation, int theInteger1, int theInteger2,
	       int theInteger3, double theDouble1, double theDouble2,
	       double theDouble3);

	// typeOfExcitation == 4
	EXCard(int theTypeOfExcitation, int theInteger3, double theDouble1,
	       double theDouble2, double theDouble3, double theDouble4,
	       double theDouble5, double theDouble6);
	// The rest
	EXCard(int theTypeOfExcitation, int theInteger1, int theInteger2,
	       int theInteger3, double theDouble1, double theDouble2,
	       double theDouble3, double theDouble4, double theDouble5,
	       double theDouble6);

	int getTypeOfExitation() const;
	int getInteger1() const;
	int getInteger2() const;
	int getInteger3() const;
	double getDouble1() const;
	double getDouble2() const;
	double getDouble3() const;
	double getDouble4() const;
	double getDouble5() const;
	double getDouble6() const;

	QString getCard();

private:
	int typeOfExcitation;
	int integer1;
	int integer2;
	int integer3;
	double double1;
	double double2;
	double double3;
	double double4;
	double double5;
	double double6;
};

#endif // EXCARD_H

