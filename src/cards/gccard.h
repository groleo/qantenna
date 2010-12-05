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

#ifndef GCCARD_H
#define GCCARD_H

#include "genericcard.h"
#include <QString>

/**
 * \class GCCard Set parameters to taper the segment lengths and radius from one
 * end of the wire to the other. Used as a second card for GW.
 */
class GCCard : public GenericCard
{
public:
  GCCard(double theRatioLenghtToLenght, double theRadiusFirstSegment,
         double theRadiusLastSegment);

  double getRatioLenghtToLenght() const;
  double getRadiusFirstSegment() const;
  double getRadiusLastSegment() const;

  QString getCard();

private:
  double ratioLenghtToLenght;
  double radiusFirstSegment;
  double radiusLastSegment;
};

#endif // GCCARD_H

