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

#ifndef PQCARD_H
#define PQCARD_H

#include "genericcard.h"
#include <QString>

/** PQ card: Print Control For Charge on Wires */

class PQCard : public GenericCard
{
public:
	PQCard(int thePrintControl, int theTagNumberToPrint);
	PQCard(int thePrintControl, int theTagNumberToPrint,
	       int theEqualToM, int theEqualToN);

	bool getBlankParameters() const;
	int getPrintControl() const;
	int getTagNumberToPrint() const;
	int getEqualToM() const;
	int getEqualToN() const;

	QString getCard();

private:
	bool blankParameters;
	/**
		IPTFLQ
		-1 - suppress printing of charge densities. This is the default condition.
		0 - (or blank) parint charge densities on segments speficied by the
		following parameters. If the following parameters are blank, charge
		densities are printed for all segments.
	*/
	int printControl;
	/// IPTAQ Tag number of the segments for which charge densities will be printed
	int tagNumberToPrint;
	/**
		IPTAQF
		Equal to m specifies the mth segment of the set of segments haveing tag
		numbers of IPTAQ. If IPTAQ is zero or blank, then IPTAQF refers to an
		absolute segment number. If IPTAQF is left blank, then charge density
		is printed for all segments.
	*/
	int equalToM;
	/**
		IPTAQT
		Equal to n specifies the nth segment of the set of segmants having tag
		numbers of IPTAQ. Charge densities are printed for segments having tag
		IPTAQT number IPTAQ starting at the mth segment in the set and ending at the nth
		segment. If IPTAQ is zero or blank, then IPTAQF and IPTAQT refer to
		absolute segment numbers. If IPTAQT refer to ablolute segment numbers.
		If IPTAQT is left blank, it is set equal to IPTAQF.
	*/
	int equalToN;
};

#endif // PQCARD_H

