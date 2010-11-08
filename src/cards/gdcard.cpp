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

#include "gdcard.h"

GDCard::GDCard(double theRelativeDielectricConstant, double theConductivity,
               double theDistanceToJoin, double theDistanceMedium2Below1)
{
  relativeDielectricConstant = theRelativeDielectricConstant;
  conductivity = theConductivity;
  distanceToJoin = theDistanceToJoin;
  distanceMedium2Below1 = theDistanceMedium2Below1;
  cardType = "GD";
}

double GDCard::getRelativeDielectricConstant() const
{
  return relativeDielectricConstant;
}

double GDCard::getConductivity() const
{
  return conductivity;
}

double GDCard::getDistanceToJoin() const
{
  return distanceToJoin;
}

double GDCard::getDistanceMedium2Below1() const
{
  return distanceMedium2Below1;
}

QString GDCard::getCard()
{
// 	QString card = cardType;
// 	/**
// 		Note that the four integer columns are empty, so we should pad the first
// 		value accordingly
// 	*/
// 	card.append(QString("%1").arg(relativeDielectricConstant,28,'f'));
// 	card.append(QString("%1").arg(conductivity,10,'f'));
// 	card.append(QString("%1").arg(distanceToJoin,10,'f'));
// 	card.append(QString("%1").arg(distanceMedium2Below1,10,'f'));
// 	card.append("\n");
// 	return card;
	return cardType + QString(" 0 0 0 0 %1 %2 %3 %4\n")
	       .arg(relativeDielectricConstant,0,'f',6)
	       .arg(conductivity,0,'f',6)
	       .arg(distanceToJoin,0,'f',6)
	       .arg(distanceMedium2Below1,0,'f',6);
}


