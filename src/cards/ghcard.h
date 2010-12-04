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

#ifndef GHCARD_H
#define GHCARD_H

#include "genericcard.h"
#include <QString>

/** Helix - Spiral Specification */

class GHCard : public GenericCard
{
public:
  /**
   * \param theTagnumber Tag number assigned to all segments of the helix or
   * spiral.
   * \param theNumberOfSegments Number of segments into which the helix or
   * spiral will be divided.
   * \param theSpacingBetweenTurns Spacing between turns.
   * \param theTotalLength Total length of the helix (HL).
   * \param theRadiusXZ0 Radius in x at z = 0.
   * \param theRadiusYZ0 Radius in y at z = 0.
   * \param theRadiusXZTotalLenght Radius in x at z = HL.
   * \param theRadiusYZTotalLenght Radius in y at z = HL.
   * \param theRadiusOfWire Radius of wire.
   */
  GHCard(int theTagNumber, int theNumberOfSegments,
         double theSpacingBetweenTurns, double theTotalLenght,
         double theRadiusXZ0, double theRadiusYZ0,
         double theRadiusXZTotalLenght, double theRadiusYZTotalLenght,
         double theRadiusOfWire);

  int getTagNumber() const;
  int getNumberOfSegments() const;
  double getSpacingBetweenTurns() const;
  double getTotalLenght() const;
  double getRadiusXZ0() const;
  double getRadiusYZ0() const;
  double getRadiusXZTotalLenght() const;
  double getRadiusYZTotalLenght() const;
  double getRadiusOfWire() const;

  QString getCard();

private:
  int tagNumber;
  int numberOfSegments;

  double spacingBetweenTurns;
  double totalLenght;
  double radiusXZ0;
  double radiusYZ0;
  double radiusXZTotalLenght;
  double radiusYZTotalLenght;
  double radiusOfWire;
};

#endif // GHCARD_H


