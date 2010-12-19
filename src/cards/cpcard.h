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

#ifndef CPCARD_H
#define CPCARD_H

#include "genericcard.h"
#include <QString>

/**
 * \brief CP card: Coupling Calculation. Request calculation of the maximum
 * coupling between segments.
 */
class CPCard : public GenericCard
{
public:
  CPCard( int theTag1, int theSegmentNumber1,
          int theTag2, int theSegmentNumber2);

  bool getSecondParameter() const;
  int getTag1() const;
  int getSegmentNumber1() const;
  int getTag2() const;
  int getSegmentNumber2() const;

  QString getCard();

private:
  bool secondParameter;
  int tag1;
  int segmentNumber1;
  int tag2;
  int segmentNumber2;
};

#endif // CPCARD_H


