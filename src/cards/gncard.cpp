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

#include "gncard.h"

GNCard::GNCard()
{
  groundType = -1;
  infiniteGround = false;
  cardType = "GN";
}

GNCard::GNCard(int theGroundType, int theNumberOfRadialWires,
               double theRelativeDielectricConstant, double theConductivity)
{
  groundType = theGroundType;
  numberOfRadialWires = theNumberOfRadialWires;
  relativeDielectricConstant = theRelativeDielectricConstant;
  conductivity = theConductivity;
  infiniteGround = true;
  cardType = "GN";
}

GNCard::GNCard(int theGroundType, int theNumberOfRadialWires,
               double theRelativeDielectricConstant, double theConductivity,
               double theDouble1, double theDouble2, double theDouble3,
               double theDouble4)
{
  groundType = theGroundType;
  numberOfRadialWires = theNumberOfRadialWires;
  relativeDielectricConstant = theRelativeDielectricConstant;
  conductivity = theConductivity;
  double1 = theDouble1;
  double2 = theDouble2;
  double3 = theDouble3;
  double4 = theDouble4;
  infiniteGround = false;
  cardType = "GN";
}

bool GNCard::getInfiniteGround()
{
  return infiniteGround;
}

int GNCard::getGroundType() const
{
  return groundType;
}

int GNCard::getNumberOfRadialWires() const
{
  return numberOfRadialWires;
}

double GNCard::getRelativeDielectricConstant() const
{
  return relativeDielectricConstant;
}

double GNCard::getConductivity() const
{
  return conductivity;
}

double GNCard::getDouble1() const
{
  return double1;
}

double GNCard::getDouble2() const
{
  return double2;
}

double GNCard::getDouble3() const
{
  return double3;
}

double GNCard::getDouble4() const
{
  return double4;
}

QString GNCard::getCard()
{
  QString card = cardType + QString(" %1").arg(groundType);

  if(groundType == -1)
  {
    card.append("\n");
    return card;
  }

  card.append(QString(" %1 0 0 %2 %3")
              .arg(numberOfRadialWires)
              .arg(relativeDielectricConstant,0,'e',6)
              .arg(conductivity,0,'e',6));

  if(infiniteGround)
  {
    card.append("\n");
    return card;
  }

  card.append(QString(" %1 %2 %3 %4\n")
              .arg(double1,0,'e',6)
              .arg(double2,0,'e',6)
              .arg(double3,0,'e',6)
              .arg(double4,0,'e',6));

  return card;
}
