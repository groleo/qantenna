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

#ifndef RADIATIONPATTERN_H
#define RADIATIONPATTERN_H
/**
	This class holds the values of one line of values of the radiation pattern
	as parsed by NECOutputParser.
	It doesn't need to much description as it just stores values. If in doubt,
	read a NEC output file.
*/
class RadiationPattern
{
public:
	RadiationPattern( double newThetaAngle, double newPhiAngle,
	double newVerticalGain, double newHorizontalGain, double newTotalGain,
	double newAxialPolarization, double newTiltDegreesPolarization,
	int newPolarizationSense,
	double newEThetaMagnitude, double newEThetaPhase,
	double newEPhiMagnitude, double newEPhiPhase );

	double GetThetaAngle() const;
	double GetPhiAngle() const;
	double GetVerticalGain() const;
	double GetHorizontalGain() const;
	double GetTotalGain() const;
	double GetAxialPolarization() const;
	double GetTiltDegreesPolarization() const;
	int GetPolarizationSense() const;
	double GetEThetaMagnitude() const;
	double GetEThetaPhase() const;
	double GetEPhiMagnitude() const;
	double GetEPhiPhase() const;

protected:
	/* Angles */
	double thetaAngle;
	double phiAngle;
	/* Power gains. We will use convert them from dB to absolute units */
	double verticalGain;
	double horizontalGain;
	double totalGain;
	/* Polarization */
	double axialPolarization;
	double tiltDegreesPolarization;
	/**
		Sense possible values:
		0: linear
		1: right
		2: left
	*/
	int polarizationSense;
	/* Electric field - Theta */
	double eThetaMagnitude;
	double eThetaPhase;
	/* Electric field - Phi */
	double ePhiMagnitude;
	double ePhiPhase;
};

#endif //RADIATIONPATTERN_H
