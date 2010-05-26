/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
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

#include "radiationpattern.h"
#include <math.h>

RadiationPattern::RadiationPattern( double newThetaAngle, double newPhiAngle,
	double newVerticalGain, double newHorizontalGain, double newTotalGain,
	double newAxialPolarization, double newTiltDegreesPolarization,
	int newPolarizationSense,
	double newEThetaMagnitude, double newEThetaPhase,
	double newEPhiMagnitude, double newEPhiPhase )
{
	thetaAngle = newThetaAngle;
	phiAngle = newPhiAngle;

	///Gains. We will convert it from dB to absolute units
	verticalGain = pow(10.0,(newVerticalGain/10.0));
	horizontalGain = pow(10.0,(newHorizontalGain/10.0));
	totalGain = pow(10.0,(newTotalGain/10.0));

	axialPolarization = newAxialPolarization;
	tiltDegreesPolarization = newTiltDegreesPolarization;
	polarizationSense = newPolarizationSense;
	eThetaMagnitude = newEThetaMagnitude;
	eThetaPhase = newEThetaPhase;
	ePhiMagnitude = newEPhiMagnitude;
	ePhiPhase = newEPhiPhase;
}

double RadiationPattern::GetThetaAngle() const
{
	return thetaAngle;
}

double RadiationPattern::GetPhiAngle() const
{
	return phiAngle;
}

double RadiationPattern::GetVerticalGain() const
{
	return verticalGain;
}

double RadiationPattern::GetHorizontalGain() const
{
	return horizontalGain;
}

double RadiationPattern::GetTotalGain() const
{
	return totalGain;
}

double RadiationPattern::GetAxialPolarization() const
{
	return axialPolarization;
}

double RadiationPattern::GetTiltDegreesPolarization() const
{
	return tiltDegreesPolarization;
}

int RadiationPattern::GetPolarizationSense() const
{
	return polarizationSense;
}

double RadiationPattern::GetEThetaMagnitude() const
{
	return eThetaMagnitude;
}

double RadiationPattern::GetEThetaPhase() const
{
	return eThetaPhase;
}

double RadiationPattern::GetEPhiMagnitude() const
{
	return ePhiMagnitude;
}

double RadiationPattern::GetEPhiPhase() const
{
	return ePhiPhase;
}

