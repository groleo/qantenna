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

#include "gfcard.h"

GFCard::GFCard(int theTableOfCoodinates)
{
	tableOfCoordinates = theTableOfCoodinates;
	cardType = "GF";
}

int GFCard::getTheTableOfCoordinates() const
{
	return tableOfCoordinates;
}

QString GFCard::getCard()
{
	return cardType + QString(" %1\n").arg(tableOfCoordinates);
}


