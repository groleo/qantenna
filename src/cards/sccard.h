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

#ifndef SCCARD_H
#define SCCARD_H

#include "genericcard.h"
#include <QString>

/** SC card: extra card following a SP, SM or SC card */

class SCCard : public GenericCard
{
public:
	/// Following a SP card with just one more coordinate needed
	SCCard(int thePatchShape, double theXCoordinateCorner3,
	       double theYCoordinateCorner3, double theZCoordinateCorner3);
	/// Following a SM card (no patchShape)
	SCCard(double theXCoordinateCorner3, double theYCoordinateCorner3,
	       double theZCoordinateCorner3);
	/// Following a SP card with two more coordinate needed
	SCCard(int thePatchShape, double theXCoordinateCorner3,
	       double theYCoordinateCorner3, double theZCoordinateCorner3,
	       double theXCoordinateCorner4, double theYCoordinateCorner4,
	       double theZCoordinateCorner4);

	bool getPatchShapeExists() const;
	bool getFourCorners() const;
	int getPatchShape() const;
	double getXCoordinateCorner3() const;
	double getYCoordinateCorner3() const;
	double getZCoordinateCorner3() const;
	double getXCoordinateCorner4() const;
	double getYCoordinateCorner4() const;
	double getZCoordinateCorner4() const;

	QString getCard();

private:
	bool patchShapeExists;
	bool fourCorners;
	int patchShape;
	double xCoordinateCorner3;
	double yCoordinateCorner3;
	double zCoordinateCorner3;
	double xCoordinateCorner4;
	double yCoordinateCorner4;
	double zCoordinateCorner4;
};

#endif // SCCARD_H

