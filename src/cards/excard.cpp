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

#include "excard.h"

EXCard::EXCard(int theTypeOfExcitation, int theInteger1, int theInteger2,
               int theInteger3, double theDouble1, double theDouble2,
               double theDouble3)
{
  typeOfExcitation = theTypeOfExcitation;
  integer1 = theInteger1;
  integer2 = theInteger2;
  integer3 = theInteger3;
  double1 = theDouble1;
  double2 = theDouble2;
  double3 = theDouble3;
  cardType = "EX";
}

EXCard::EXCard(int theTypeOfExcitation, int theInteger3, double theDouble1,
               double theDouble2, double theDouble3, double theDouble4,
               double theDouble5, double theDouble6)
{
  typeOfExcitation = theTypeOfExcitation;
  integer3 = theInteger3;
  double1 = theDouble1;
  double2 = theDouble2;
  double3 = theDouble3;
  double4 = theDouble4;
  double5 = theDouble5;
  double6 = theDouble6;
  cardType = "EX";
}

EXCard::EXCard(int theTypeOfExitation, int theInteger1, int theInteger2,
               int theInteger3, double theDouble1, double theDouble2,
               double theDouble3, double theDouble4, double theDouble5,
               double theDouble6)
{
  typeOfExcitation = theTypeOfExitation;
  integer1 = theInteger1;
  integer2 = theInteger2;
  integer3 = theInteger3;
  double1 = theDouble1;
  double2 = theDouble2;
  double3 = theDouble3;
  double4 = theDouble4;
  double5 = theDouble5;
  double6 = theDouble6;
  cardType = "EX";
}

int EXCard::getTypeOfExitation() const
{
  return typeOfExcitation;
}

int EXCard::getInteger1() const
{
  return integer1;
}

int EXCard::getInteger2() const
{
  return integer2;
}

int EXCard::getInteger3() const
{
  return integer3;
}

double EXCard::getDouble1() const
{
  return double1;
}

double EXCard::getDouble2() const
{
  return double2;
}

double EXCard::getDouble3() const
{
  return double3;
}

double EXCard::getDouble4() const
{
  return double4;
}

double EXCard::getDouble5() const
{
  return double5;
}

double EXCard::getDouble6() const
{
  return double6;
}

QString EXCard::getCard()
{
  QString card = cardType;
  //FIXME The description of this card should be read from NEC2++'s doc and re-written

  // Integer columns
  if(typeOfExcitation == 4)
  {
    card.append(QString(" %1 0 0 0").arg(typeOfExcitation));
  }
  else
  {
    card.append(QString(" %1 %2 %3 %4")
                .arg(typeOfExcitation)
                .arg(integer1)
                .arg(integer2)
                .arg(integer3));
  }

  // Floating points
  if( (typeOfExcitation==0) or (typeOfExcitation==5))
  {
    card.append(QString(" %1 %2 %3\n")
                .arg(double1,0,'e',6)
                .arg(double2,0,'e',6)
                .arg(double3,0,'e',6));
  }
  else
  {
    card.append(QString(" %1 %2 %3 %4 %5 %6\n")
                .arg(double1,0,'e',6)
                .arg(double2,0,'e',6)
                .arg(double3,0,'e',6)
                .arg(double4,0,'e',6)
                .arg(double5,0,'e',6)
                .arg(double6,0,'e',6));
  }
  return card;
}
