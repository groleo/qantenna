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

#ifndef NTCARD_H
#define NTCARD_H

#include "genericcard.h"
#include <QString>

/**
 * \brief NT card: networks. Generate a two-port nonradiating network connected
 * between any two segments in the structure.
 *
 * The characteristics of the network are specified by its short-circuit
 * admittance matrix elements. For the special case of a transmission line, a
 * separate card is provided for convenience although the mathematical method is
 * the same as for networks. Refer to the TL card.
 */
class NTCard : public GenericCard
{
public:
  /// equalToM == -1
  NTCard(int theTagNumber, int theEqualToM);
  /// equalToM != -1
  NTCard(int theTagNumber, int theEqualToM, int theTagNumber2,
         int theEqualToN, double theReal11, double theImaginary11,
         double theReal12, double theImaginary12, double theReal22,
         double theImaginary22);

  int getTagNumber() const;
  int getEqualToM() const;
  int getTagNumber2() const;
  int getEqualToN() const;
  double getReal11() const;
  double getImaginary11() const;
  double getReal12() const;
  double getImaginary12() const;
  double getReal22() const;
  double getImaginary22() const;

  QString getCard();

private:
  /**
    Tag number of the segment to which port one of the network is connected.
    This tag number along with the number to be given in (I2), which identifies
    the position of the segment in a set of equal tag numbers, uniquely defines
    the segment for port one. Blank or zero here implies that the segment will
    be identified, using the absolute segment number in the next location
  */
  int tagNumber;
  /**
    Specifies the mth segment of the set of segments whose tag numbers are
    equal to the number set by the previous parameter. If the previous parameter
    is zero, the number in (12) is the absolute segment number corresponding to
    end one of the network. A minus one in this field will nullify all previous
    network and transmission line connections. The rest of the card is left
    blank in this case.
  */
  int equalToM;
  /// Same as tagNumber for port 2
  int tagNumber2;
  /// Same as equalToM for port 2
  int equalToN;
  /**
    The six floating-point fields are used to specify the real and imaginary
    parts of three short circuit admittance matrix elements (1, 1), (1, 2), and
    (2, 2), respectively. The admittance matrix is symmetric so it is
    unnecessary to specify element (2, 1).
  */
  double real11;
  double imaginary11;
  double real12;
  double imaginary12;
  double real22;
  double imaginary22;
};

#endif // NTCARD_H


