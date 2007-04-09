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

#ifndef NENHCARDS_H
#define NENHCARDS_H

#include "genericcard.h"
#include <QString>

/**
	NE and NH cards: Near Fields
	Request calculation of near electric fields in the vicinity of the antenna
	(NE) and to request near magnetic fields (NH).
*/

class NENHCards : public GenericCard
{
public:
	NENHCards(bool isItNECard, int theCoordinateSystemType,
	          int theNumberOfPointsXR, int theNumberOfPointsYPhi,
	          int theNumberOfPointsZTheta, double theCoordinateXR,
	          double theCoordinateYPhi, double theCoordinateZTheta,
	          double theIncrementXR, double theIncrementYPhi,
	          double theIncrementZTheta);

	bool getIsNECard() const;
	int getCoordinateSystemType() const;
	int getNumberOfPointsXR() const;
	int getNumberOfPointsYPhi() const;
	int getNumberOfPointsZTheta() const;
	double getCoordinateXR() const;
	double getCoordinateYPhi() const;
	double getCoordinateZTheta() const;
	double getIncrementXR() const;
	double getIncrementYPhi() const;
	double getIncrementZTheta() const;

QString getCard();

private:
	/**
		true = NE card
		false = NH card
	*/
	bool isNECard;
	/**
		0 - rectangular coordinates will be used.
		1 - spherical coordinates will be used.
	*/
	int coordinateSystemType;
	/**
		coordinateSystemType ==
			0: Number of points desired in the X
			1: Number of points desired in the r
		The value 1 is assumed for any field left blank.
	*/
	int numberOfPointsXR;
	/**
		coordinateSystemType ==
			0: Number of points desired in the Y
			1: Number of points desired in the Phi
		The value 1 is assumed for any field left blank.
	*/
	int numberOfPointsYPhi;
	/**
		coordinateSystemType ==
			0: Number of points desired in the Z
			1: Number of points desired in the Theta
		The value 1 is assumed for any field left blank.
	*/
	int numberOfPointsZTheta;
	double coordinateXR;
	double coordinateYPhi;
	double coordinateZTheta;
	double incrementXR;
	double incrementYPhi;
	double incrementZTheta;
};

#endif // NENHCARDS_H




