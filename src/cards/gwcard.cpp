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

#include "gwcard.h"

GWCard::GWCard(int theTagNumber, int theNumberOfSegments, double theXWire1,
               double theYWire1, double theZWire1, double theXWire2,
               double theYWire2, double theZWire2, double theWireRadius)
{
  tagNumber = theTagNumber;
  numberOfSegments = theNumberOfSegments;
  xWire1 = theXWire1;
  yWire1 = theYWire1;
  zWire1 = theZWire1;
  xWire2 = theXWire2;
  yWire2 = theYWire2;
  zWire2 = theZWire2;
  wireRadius = theWireRadius;
  cardType = "GW";
}

int GWCard::getTagNumber() const
{
  return tagNumber;
}

int GWCard::getNumberOfSegments() const
{
  return numberOfSegments;
}

double GWCard::getXWire1() const
{
  return xWire1;
}

double GWCard::getYWire1() const
{
  return yWire1;
}

double GWCard::getZWire1() const
{
  return zWire1;
}

double GWCard::getXWire2() const
{
  return xWire2;
}

double GWCard::getYWire2() const
{
  return yWire2;
}

double GWCard::getZWire2() const
{
  return zWire2;
}

double GWCard::getWireRadius() const
{
  return wireRadius;
}

QString GWCard::getCard()
{
  return cardType + QString(" %1 %2 %3 %4 %5 %6 %7 %8 %9\n")
         .arg(tagNumber)
         .arg(numberOfSegments)
         .arg(xWire1,0,'e',6)
         .arg(yWire1,0,'e',6)
         .arg(zWire1,0,'e',6)
         .arg(xWire2,0,'e',6)
         .arg(yWire2,0,'e',6)
         .arg(zWire2,0,'e',6)
         .arg(wireRadius,0,'e',6);
}






