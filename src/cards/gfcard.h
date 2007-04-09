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

#ifndef GFCARD_H
#define GFCARD_H

#include "genericcard.h"
#include <QString>

/** GF card:  Read NGF File */

class GFCard : public GenericCard
{
public:
	GFCard(int theTableOfCoordinates);

	int getTheTableOfCoordinates() const;

	QString getCard();

private:
	/**
		Prints a table of the coordinates of the ends of all segments in the NGF if
		I1 not equal to 0. Normal printing otherwise.
	*/
	int tableOfCoordinates;
};

#endif // GFCARD_H

