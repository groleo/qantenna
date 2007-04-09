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

#ifndef XQCARD_H
#define XQCARD_H

#include "genericcard.h"
#include <QString>

/**
	XQ card: execute
	Cause program execution at points in the data stream where execution is not
	automatic.  Options on the card also allow for automatic generation of
	radiation patterns in either of two vertical cuts.
*/

class XQCard : public GenericCard
{
public:
	XQCard(int theOptions);

	int getOptions() const;

	void setOptions(int theOptions);

	QString getCard();

private:
	/**
		Options controlled by (I1) are:
		0 - no patterns requested (normal case).
		1 - generates a pattern cut in the XZ plane, i.e., phi = 0 degrees and
		theta varies from 0 degrees to 90 degrees in 1 degree steps.
		2 - generates a pattern cut in the YZ plane, i.e., phi = 90 degrees. Theta
		varies from 0 degrees to 90 degrees in 1 degree steps.
		3 - generates both of the cuts described for the values 1 and 2.
	*/
	int options;
};

#endif // XQCARD_H

