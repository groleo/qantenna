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

#ifndef SMCARD_H
#define SMCARD_H

#include "genericcard.h"
#include <QString>

/**
	SM card: multiple patch surface
	Cover a rectangular region with surface patches.
*/

class SMCard : public GenericCard
{
public:
	SMCard(int theCorners12Divisions, int theCorners34Divisions,
	       double theXCoordinateCorner1, double theYCoordinateCorner1,
	       double theZCoordinateCorner1, double theXCoordinateCorner2,
	       double theYCoordinateCorner2, double theZCoordinateCorner2);

	int getCorners12Divisions() const;
	int getCorners34Divisions() const;
	double getXCoordinateCorner1() const;
	double getYCoordinateCorner1() const;
	double getZCoordinateCorner1() const;
	double getXCoordinateCorner2() const;
	double getYCoordinateCorner2() const;
	double getZCoordinateCorner2() const;

	QString getCard();

private:
	/**
		The rectangular surface is divided into corners12Divisions patches from
		corner 1 to corner 2
	*/
	int corners12Divisions;
	/**
		The rectangular surface is divided into corners34Divisions patches from
		corner 3 to corner 4
	 */
	int corners34Divisions;
	double xCoordinateCorner1;
	double yCoordinateCorner1;
	double zCoordinateCorner1;
	double xCoordinateCorner2;
	double yCoordinateCorner2;
	double zCoordinateCorner2;
};

#endif // SMCARD_H

