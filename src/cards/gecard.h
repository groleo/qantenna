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

#ifndef GECARD_H
#define GECARD_H

#include "genericcard.h"
#include <QString>

/** GE card: End geometry input */

class GECard : public GenericCard
{
public:
	GECard(int theGeometryGroundPlane);

	int getGeometryGroundPlane() const;

	QString getCard();

private:
	/**
		pflag - Geometry ground plain flag.

		0 - no ground plane is present.
		1 - Indicates a ground plane is present. Structure symmetry is modified as
		required, and the current expansion is modified so that the currents an
		segments touching the ground (X, Y plane) are interpolated to their images
		below the ground (charge at base is zero)
		1 - Indicates a ground is present. Structure symmetry is modified as
		required. Current expansion, however, is not modified, Thus, currents on
		segments touching the ground will go to zero at the ground.
	*/
	int geometryGroundPlane;

};

#endif // GECARD_H

