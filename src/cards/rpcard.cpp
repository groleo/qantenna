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

#include "rpcard.h"

RPCard::RPCard(int theModeOfCalculation, int theNumberOfValuesOfTheta,
               int theNumberOfValuesOfPhi, int theXNDA, double theInitialTheta,
               double theInitialPhi, double theIncrementTheta,
               double theIncrementPhi, double theRadialDistance,
               double theGainNormalization)
{
  modeOfCalculation = theModeOfCalculation;
  numberOfValuesOfTheta = theNumberOfValuesOfTheta;
  numberOfValuesOfPhi = theNumberOfValuesOfPhi;
  xnda = theXNDA;
  initialTheta = theInitialTheta;
  initialPhi = theInitialPhi;
  incrementTheta = theIncrementTheta;
  incrementPhi = theIncrementPhi;
  radialDistance = theRadialDistance;
  gainNormalization = theGainNormalization;
  cardType = "RP";
}

int RPCard::getModeOfCalculation() const
{
  return modeOfCalculation;
}

int RPCard::getNumberOfValuesOfTheta() const
{
  return numberOfValuesOfTheta;
}

int RPCard::getNumberOfValuesOfPhi() const
{
  return numberOfValuesOfPhi;
}

int RPCard::getXNDA() const
{
  return xnda;
}

double RPCard::getInitialTheta() const
{
  return initialTheta;
}

double RPCard::getInitialPhi() const
{
  return initialPhi;
}

double RPCard::getIncrementTheta() const
{
  return incrementTheta;
}

double RPCard::getIncrementPhi() const
{
  return incrementPhi;
}

double RPCard::getRadialDistance() const
{
  return radialDistance;
}

double RPCard::getGainMormalization() const
{
  return gainNormalization;
}

void RPCard::setModeOfCalculation(int theModeOfCalculation)
{
  modeOfCalculation = theModeOfCalculation;
}

void RPCard::setNumberOfValuesOfTheta(int theNumberOfValuesOfTheta)
{
  numberOfValuesOfTheta = theNumberOfValuesOfTheta;
}

void RPCard::setNumberOfValuesOfPhi(int theNumberOfValuesOfPhi)
{
  numberOfValuesOfPhi = theNumberOfValuesOfPhi;
}

void RPCard::setXNDA(int theXNDA)
{
  xnda = theXNDA;
}

void RPCard::setInitialTheta(double theInitialTheta)
{
  initialTheta = theInitialTheta;
}

void RPCard::setInitialPhi(double theInitialPhi)
{
  initialPhi = theInitialPhi;
}

void RPCard::setIncrementTheta(double theIncrementTheta)
{
  incrementTheta = theIncrementTheta;
}

void RPCard::setIncrementPhi(double theIncrementPhi)
{
  incrementPhi = theIncrementPhi;
}

void RPCard::setRadialDistance(double theRadialDistance)
{
  radialDistance = theRadialDistance;
}

void RPCard::setGainMormalization(double theGainNormalization)
{
  gainNormalization = theGainNormalization;
}

QString RPCard::getCard()
{
  return cardType + QString(" %1 %2 %3 %4 %5 %6 %7 %8 %9 %10\n")
         .arg(modeOfCalculation)
         .arg(numberOfValuesOfTheta)
         .arg(numberOfValuesOfPhi)
         .arg(xnda)
         .arg(initialTheta,0,'e',6)
         .arg(initialPhi,0,'e',6)
         .arg(incrementTheta,0,'e',6)
         .arg(incrementPhi,0,'e',6)
         .arg(radialDistance,0,'e',6)
         .arg(gainNormalization,0,'e',6);
}





