/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
 *   Gustavo González - gonzalgustavo en/at gmail.com                      *
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
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QString>
#include <QVector>
/**
	Primitive class is used as a basic structure to implement a list (primitiveList)
	with lines and patches (polymorphism). Its functions are overloaded in line
	and patch classes.
*/
class Primitive {
public:
	virtual ~Primitive() {};

	/// Set card label.
	virtual void SetLabel(QString newLabel) = 0 ;

	/// Set tag number.
	virtual void SetTagNumber(int newTagNumber) = 0 ;

	/// This function isn't used yet, but are usefull for futures improvements.
	virtual void SetWidth(double newWidth) = 0 ;

	/// This function isn't used yet, but are usefull for futures improvements.
	virtual void SetColor(double newColor) = 0 ;

	/// Set parameter that are used to process card as GM, GX, and others.
	virtual void SetCardParameter(int newCardParameter) = 0 ;

	/// Set parameter that are used to process card as GM, GX, and others.
	virtual void SetCardParameter1(int newCardParameter) = 0 ;

	/// This function rotates the line through the x, y and z axis, ang degrees.
	/// X angle is in ang[0], Y angle in ang[1] and Z angle in ang[3].
	virtual void Rotate(QVector<double> & ang) = 0;

	/// This function moves the line to the x, y and z that are in pos[0], pos[1]
	/// and pos[3].
	virtual void Move(QVector<double> & pos) = 0;

	/// This function reflect the line along x (reflection in Y-Z plane), y or z.
	virtual void Reflect(bool x, bool y, bool z) = 0 ;

	/// Get label.
	virtual QString GetLabel() = 0 ;

	/// Get tag number.
	virtual int GetTagNumber() = 0 ;

	/// Get card parameter.
	virtual int GetCardParameter() = 0 ;

	/// Get card parameter1.
	virtual int GetCardParameter1() = 0 ;

	/// Get end1.
	virtual QVector<double> GetEnd1() = 0;

	/// Get end2.
	virtual QVector<double> GetEnd2() = 0;

	/// This function isn't used yet, but are usefull for futures improvements.
	virtual double GetWidth() = 0 ;

	/// This function isn't used yet, but are usefull for futures improvements.
	virtual double GetColor() = 0 ;

	/// This finction calculates the maximum module.
	virtual double CalculateMaxModule() = 0 ;
};

#endif
