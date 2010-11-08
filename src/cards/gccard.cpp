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

#include "gccard.h"

GCCard::GCCard(double theRatioLenghtToLenght, double theRadiusFirstSegment,
               double theRadiusLastSegment)
{
  ratioLenghtToLenght = theRatioLenghtToLenght;
  radiusFirstSegment = theRadiusFirstSegment;
  radiusLastSegment = theRadiusLastSegment;
  cardType = "GC";
}

double GCCard::getRatioLenghtToLenght() const
{
  return ratioLenghtToLenght;
}

double GCCard::getRadiusFirstSegment() const
{
  return radiusFirstSegment;
}

double GCCard::getRadiusLastSegment() const
{
  return radiusLastSegment;
}

QString GCCard::getCard()
{
  return cardType + QString(" 0 0 %1 %2 %3\n")
         .arg(ratioLenghtToLenght,0,'e',6)
         .arg(radiusFirstSegment,0,'e',6)
         .arg(radiusLastSegment,0,'e',6);
}


