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

#ifndef TLCARD_H
#define TLCARD_H

#include "genericcard.h"
#include <QString>

/**
	TL card: Transmission Line
	Generate a transmission line between any two points on the structure.
	Characteristic impedance, length, and shunt admittance are the defining
	parameters.
*/

class TLCard : public GenericCard
{
public:
	/// equalToM == -1
	TLCard(int theTagNumber, int theEqualToM);
	/// equalToM != -1
	TLCard(int theTagNumber, int theEqualToM, int theTagNumber2,
	       int theEqualToN, double theCharacteristicImpedance, double theLenght,
	       double theRealAdmittancePort1, double theImaginaryAdmittancePort1,
	       double theRealAdmittancePort2, double theImaginaryAdmittancePort2);

	int getTagNumber() const;
	int getEqualToM() const;
	int getTagNumber2() const;
	int getEqualToN() const;
	double getCharacteristicImpedance() const;
	double getLenght() const;
	double getRealAdmittancePort1() const;
	double getImaginaryAdmittancePort1() const;
	double getRealAdmittancePort2() const;
	double getImaginaryAdmittancePort2() const;

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
		The characteristic impedance of the transmission line in ohms. A negative
		sign in front of the characteristic impedance will act as a flag for
		generating the transmission line with a 180 degree phase reversal (crossed
		line) if this is desired.
	*/
	double characteristicImpedance;
	/**
		The length of transmission line in meters.  If this field is left blank,
		the program will use the straight line distance between the specified
		connection points.
	*/
	double lenght;
	/**
		The remaining four floating-point fields are used to specify the real and
		imaginary parts of the shunt admittances at end one and two, respectively.
	*/
	/// Real part of the shunt admittance in mhos at end one.
	double realAdmittancePort1;
	/// Imaginary part of the shunt admittance in mhos at end one.
	double imaginaryAdmittancePort1;
	/// Real part of the shunt admittance in mhos at end two
	double realAdmittancePort2;
	/// Imaginary part of the shunt admittance in mhos at end two.
	double imaginaryAdmittancePort2;
};

#endif // TLCARD_H



