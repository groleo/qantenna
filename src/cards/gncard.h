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

#ifndef GNCARD_H
#define GNCARD_H

#include "genericcard.h"
#include <QString>

/**
  GN card: Ground Parameters
  Specify the relative dielectric constant and conductivity of ground in the
  vicinity of the antenna. In addition, a second set of ground parameters for
  a second medium can be specified, or a radial wire ground screen can be
  modeled using a reflection coefficient approximation.
*/

class GNCard : public GenericCard
{
public:
  /// groundType == -1  - Free space conditions
  GNCard();
  /// Infinite ground plane. No floating points used.
  GNCard(int theGroundType, int theNumberOfRadialWires,
         double theRelativeDielectricConstant, double theConductivity);
  /// Normal cases
  GNCard(int theGroundType, int theNumberOfRadialWires,
         double theRelativeDielectricConstant, double theConductivity,
         double theDouble1, double theDouble2, double theDouble3,
         double theDouble4);

  bool getInfiniteGround();
  int getGroundType() const;
  int getNumberOfRadialWires() const;
  double getRelativeDielectricConstant() const;
  double getConductivity() const;
  double getDouble1() const;
  double getDouble2() const;
  double getDouble3() const;
  double getDouble4() const;

  QString getCard();

private:
  bool infiniteGround;
  int groundType;
  int numberOfRadialWires;
  double relativeDielectricConstant;
  double conductivity;
  double double1;
  double double2;
  double double3;
  double double4;
};

#endif // GNCARD_H

