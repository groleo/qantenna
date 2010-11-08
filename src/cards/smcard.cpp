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

#include "smcard.h"

SMCard::SMCard(int theCorners12Divisions, int theCorners34Divisions,
               double theXCoordinateCorner1, double theYCoordinateCorner1,
               double theZCoordinateCorner1, double theXCoordinateCorner2,
               double theYCoordinateCorner2, double theZCoordinateCorner2)
{
  corners12Divisions = theCorners12Divisions;
  corners34Divisions = theCorners34Divisions;
  xCoordinateCorner1 = theXCoordinateCorner1;
  yCoordinateCorner1 = theYCoordinateCorner1;
  zCoordinateCorner1 = theZCoordinateCorner1;
  xCoordinateCorner2 = theXCoordinateCorner2;
  yCoordinateCorner2 = theYCoordinateCorner2;
  zCoordinateCorner2 = theZCoordinateCorner2;
  cardType = "SM";
}

int SMCard::getCorners12Divisions() const
{
  return corners12Divisions;
}

int SMCard::getCorners34Divisions() const
{
  return corners34Divisions;
}

double SMCard::getXCoordinateCorner1() const
{
  return xCoordinateCorner1;
}

double SMCard::getYCoordinateCorner1() const
{
  return yCoordinateCorner1;
}

double SMCard::getZCoordinateCorner1() const
{
  return zCoordinateCorner1;
}

double SMCard::getXCoordinateCorner2() const
{
  return xCoordinateCorner2;
}

double SMCard::getYCoordinateCorner2() const
{
  return yCoordinateCorner2;
}

double SMCard::getZCoordinateCorner2() const
{
  return zCoordinateCorner2;
}

QString SMCard::getCard()
{
  return cardType + QString(" %1 %2 %3 %4 %5 %6 %7 %8\n")
         .arg(corners12Divisions)
         .arg(corners34Divisions)
         .arg(xCoordinateCorner1,0,'e',6)
         .arg(yCoordinateCorner1,0,'e',6)
         .arg(zCoordinateCorner1,0,'e',6)
         .arg(xCoordinateCorner2,0,'e',6)
         .arg(yCoordinateCorner2,0,'e',6)
         .arg(zCoordinateCorner2,0,'e',6);
}


