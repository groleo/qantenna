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

#ifndef GDCARD_H
#define GDCARD_H

#include "genericcard.h"
#include <QString>

/**
 * \brief GD card: Additional Ground Parameters. Specify the ground parameters
 * of a second medium which is not in the immediate vicinity of the antenna.
 *
 * This card may only be used if a GN card has also been used. It does not
 * affect the field of surface patches.
 */
class GDCard : public GenericCard
{
public:
  GDCard(double theRelativeDielectricConstant, double theConductivity,
         double theDistanceToJoin, double theDistanceMedium2Below1);

  double getRelativeDielectricConstant() const;
  double getConductivity() const;
  double getDistanceToJoin() const;
  double getDistanceMedium2Below1() const;

  QString getCard();

private:
  /// Relative dielectric constant of the second medium.
  double relativeDielectricConstant;
  /// Conductivity in mhos/mecer of the second medium.
  double conductivity;
  /**
    Distance in meters from the origin of the coordinate system to the join
    between medium 1 and 2. This distance is either the radius of the circle
    where the two media Join or the distance out the plus X axis to where the
    two media join in a line parallel to the Y axis. Specification of the
    circular or linear option is on the RP cart.
  */
  double distanceToJoin;
  /**
    Distance in meters (positive or zero) by which the surface of medium 2 is
    below medium 1.
  */
  double distanceMedium2Below1;
};

#endif // GDCARD_H


