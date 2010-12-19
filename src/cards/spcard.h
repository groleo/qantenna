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

#ifndef SPCARD_H
#define SPCARD_H

#include "genericcard.h"
#include <QString>

/**
 * \brief SP card: surface patch, input parameters of a single surface patch.
 */
class SPCard : public GenericCard
{
public:
  /**
   * \param thePatchShape Selects patch shape.
   * - 0: (default) arbitrary patch shape.
   * - 1: rectangular patch.
   * - 2: triangular patch.
   * - 3: quadrilateral patch.
   * \param theXCoordinateCorner1 X coordinate corner 1.
   * - patchShape == 0:  X coordinate of patch center.
   * - patchShape != 0:  X coordinate of corner 1.
   * \param theYCoordinateCorner1 Y coordinate corner 1.
   * - patchShape == 0: Y coordinate of patch center.
   * - patchShape != 0: Y coordinate of corner 1.
   * \param theZCoordinateCorner1 Z coordinate center 1.
   * - patchShape == 0: Z coordinate of patch center.
   * - patchShape != 0: Z coordinate of corner 1.
   * \param theXCoordinateCorner2 X coordinate corner 2.
   * - patchShape == 0: elevation angle above the X-Y plane of outward normal
   *  vector (degrees).
   * - patchShape != 0: X coordinate of corner 2.
   * \param theYCoordinateCorner2 Y coordinate corner 2.
   * - patchShape == 0: azimuth angle from X-axis of outward normal vector
   *  (degrees).
   * - patchShape != 0: Y coordinate of corner 2.
   * \param theZCoordinateCorner2 Z coordinate corner 2.
   * - patchShape == 0: patch area (square of units used).
   * - patchShape != 0: Z coordinate of corner 2.
   */
  SPCard(int thePatchShape, double theXCoordinateCorner1,
         double theYCoordinateCorner1, double theZCoordinateCorner1,
         double theXCoordinateCorner2, double theYCoordinateCorner2,
         double theZCoordinateCorner2 );

  int getPatchShape() const;
  double getXCoordinateCorner1() const;
  double getYCoordinateCorner1() const;
  double getZCoordinateCorner1() const;
  double getXCoordinateCorner2() const;
  double getYCoordinateCorner2() const;
  double getZCoordinateCorner2() const;

  QString getCard();

private:
  int patchShape;
  double xCoordinateCorner1;
  double yCoordinateCorner1;
  double zCoordinateCorner1;
  double xCoordinateCorner2;
  double yCoordinateCorner2;
  double zCoordinateCorner2;
};

#endif // SPCARD_H
