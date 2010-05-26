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

#ifndef LDCARD_H
#define LDCARD_H

#include "genericcard.h"
#include <QString>

/**
	LD card: loading
	Specify the impedance loading on one segment or a number of segments. Series
	and parallel RLC circuits can be generated. In addition, a finite
	conductivity can be specified for segments.
*/

class LDCard : public GenericCard
{
public:
	/// loadType == -1
	LDCard(int theLoadType);
	/// loadType == 0, 1, 2 or 3
	LDCard(int theLoadType, int theTagNumber, int theEqualToM, int theEqualToN,
	       double theResistance, double theInductance, double theCapacitance);
	/// loadType = 4
	LDCard(int theLoadType, int theTagNumber, int theEqualToM, int theEqualToN,
	       double theResistance, double theReactance);
	/// loadType == 5
	LDCard(int theLoadType, int theTagNumber, int theEqualToM, int theEqualToN,
	       double theConductivity);

	bool getShortAllLoads() const;
	int getLoadType() const;
	int getTagNumber() const;
	int getEqualToM() const;
	int getEqualToN() const;
	double getResistance() const;
	double getInductance() const;
	double getCapacitance() const;

	QString getCard();

private:
	bool shortAllLoads;
	/**
		Determines the type of loading which is used. The options are:
		-1 - short all loads (used to nullify previous loads). The remainder of the card is left blank.
		0 - series RLC, input ohms, henries, farads.
		1 - parallel RLC, input ohms, henries, farads.
		2 - series RLC, input ohms/meter, henries/meter, farads/meter.
		3 - parallel RLC, input ohms/meter, henries/meter, farads/meter.
		4 - impedance, input resistance and reactance in ohms.
		5 - wire conductivity, mhos/meter.
	*/
	int loadType;
	/**
		Identifies the wire section(s) to be loaded by its (their) tag numbers.
	*/
	int tagNumber;
	/**
		Specifies the mth segment of the set of segments whose tag numbers equal
		the tag number specified in the previous parameter. If the previous
		parameter (LDTAG) is zero, LDTAGF then specifies an absolute segment
		number. If both LDTAG and LDTAGF are zero, all segments will be loaded.
	*/
	int equalToM;
	/**
		Specifies the nth segment of the set of segments whose tag numbers equal
		the tag number specified in the parameter LDTAG. This parameter must be
		greater than or equal to the previous param- eter. The loading specified
		is applied to each of the mth through nth segments of the set of segments
		having tags equal to LDTAG. Again if LDTAG is zero, these parameters refer
		to absolute segment numbers. If LDTAGT is left blank, it is set equal to
		the previous parameter (LDTAGF).
	*/
	int equalToN;
	/**
		loadType ==
			0 or 1 : Resistance in ohms, if none, leave blank.
			2 or 3 : Resistance in ohms/meter, if none, leave blank.
			4 : Resistance in ohms.
			5 : Conductivity in mhos/meter.
	*/
	double resistance;
	/**
		loadType ==
			0 or 1 : Inductance in henries, if none, leave blank.
			2 or 3 : Inductance in henries/meter, if none, leave blank.
			4 : Reactance in ohms.
			5: no use
	*/
	double inductance;
	/**
		loadType ==
			0 or 1 : Capacitance in farads, if none, leave blank.
			2 or 3 : Capacitance in farads/meter, if none, leave blank.
			4 : no use (leave blank)
			5: no use (leave blank)
	*/
	double capacitance;
};

#endif // LDCARD_H


