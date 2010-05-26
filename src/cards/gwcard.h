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

#ifndef GWCARD_H
#define GWCARD_H

#include "genericcard.h"
#include <QString>

/**
	Wire Specification (GW)
	Generate a string of segments to represent a straight wire.
*/

class GWCard : public GenericCard
{
public:
	GWCard(int theTagNumber, int theNumberOfSegments, double theXWire1,
	       double theYWire1, double theZWire1, double theXWire2,
	       double theYWire2, double theZWire2, double theWireRadius);

	int getTagNumber() const;
	int getNumberOfSegments() const;
	double getXWire1() const;
	double getYWire1() const;
	double getZWire1() const;
	double getXWire2() const;
	double getYWire2() const;
	double getZWire2() const;
	double getWireRadius() const;

	QString getCard();

private:
	int tagNumber;
	int numberOfSegments;
	double xWire1;
	double yWire1;
	double zWire1;
	double xWire2;
	double yWire2;
	double zWire2;
	double wireRadius;
};

#endif // GWCARD_H

