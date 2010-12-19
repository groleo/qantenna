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

#ifndef FRCARD_H
#define FRCARD_H

#include "genericcard.h"
#include <QString>

/**
 * \brief FR card: specifies the frequency in MegaHertz.
 *
 * Note: for the special case of QAntenna (at the time of version 0.1 to version
 * 0.2), the number of frequency steps and the frequency increment would be set
 * to 1 in both cases in the constructor, as only one radiation pattern is
 * considered.
 */
class FRCard : public GenericCard
{
public:
  FRCard(int theTypeOfStepping, int theNumberOfFrequencySteps=1,
         double theFrequency=299.8, double theFrequencyIncrement=0);

  int getTypeOfStepping() const;
  int getNumberOfFrequencySteps() const;
  double getFrequency() const;
  double getFrequencyIncrement() const;

  void setTypeOfStepping(int theTypeOfStepping);
  void setNumberOfFrequencySteps(int theNumberOfFrequencySteps);
  void setFrequency(double theFrequency);
  void setFrequencyIncrement(double theFrequencyIncrement);

  QString getCard();

private:
  /**
    Determines the type of frequency stepping which is
    0 - linear stepping.
    1 - multiplicative stepping.
  */
  int typeOfStepping;
  /// Number of frequency steps. If this field is blank,one is assumed.
  int numberOfFrequencySteps;
  /**
    Frequency in MegaHertz
    If a frequency card does not appear in the data deck, a single frequency of
    299.8 MHz is assumed. Since the wavelength at 299.8 MHz is one meter, the
    geometry is in units of wavelengths for this case.
  */
  double frequency;
  /**
    Frequency stepping increment. If the frequency stepping is linear, this
    quantity is added to the frequency each time. If the stepping is
    multiplicative, this is the multiplication factor.
  */
  double frequencyIncrement;
};

#endif // FRCARD_H

