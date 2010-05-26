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

#ifndef GRCARD_H
#define GRCARD_H

#include "genericcard.h"
#include <QString>

/**
	Generate Cylindrical Structure (GR) \n
	Reproduce a structure while rotating about the Z-axis to form a complete
	cylindrical array and to set flags so that symmetry is utilized in the
	solution.
*/

class GRCard : public GenericCard
{
public:
	GRCard(int theTagNumberIncrement, int theNumberOfOcurrencies);

	int getTagNumberIncrement() const;
	int getNumberOfOcurrencies() const;

	QString getCard();

private:
	int tagNumberIncrement;
	int numberOfOcurrencies;

};

#endif // GRCARD_H


