/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
 *   Gustavo González - gonzalgustavo en/at gmail.com                      *
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
#include "line.h"
#include <math.h>

Line::Line()
{
	end1.append(0.0);
	end1.append(0.0);
	end1.append(0.0);

	end2.append(0.0);
	end2.append(0.0);
	end2.append(0.0);
}

Line::Line(QString newLabel, QVector<double> newEnd1, QVector<double> newEnd2,
           int newTagNumber, int newCardParameter, int newCardParameter1)
{
	label = newLabel;
	end1 = newEnd1;
	end2 = newEnd2;

	tagNumber = newTagNumber;
	cardParameter = newCardParameter;
	cardParameter1 = newCardParameter1;
}

Line::~Line()
{
}

void Line::SetLabel( QString newLabel)
{
	label = newLabel;
}

void Line::SetTagNumber( int newTagNumber)
{
	tagNumber = newTagNumber;
}

void Line::SetEnd1( double x, double y, double z)
{
	end1[0] = x;
	end1[1] = y;
	end1[2] = z;
}

void Line::SetEnd2( double x, double y, double z)
{
	end2[0] = x;
	end2[1] = y;
	end2[2] = z;
}

void Line::SetWidth( double newWidth)
{
	width = newWidth;
}

void Line::SetColor( double newColor)
{
	color = newColor;
}

void Line::SetCardParameter(int newCardParameter)
{
	cardParameter = newCardParameter;
}

void Line::SetCardParameter1(int newCardParameter)
{
	cardParameter1 = newCardParameter;
}

void Line::Rotate(QVector<double> & ang)
{
	double temp[2];
	double out[2];

	// Rotation along x axis.
	temp[0] = end1[1];
	temp[1] = end1[2];
	Rotate(temp, out, ang[0]);
	end1[1] = out[0];
	end1[2] = out[1];

	// Rotation along y axis.
	temp[0] = end1[0];
	temp[1] = end1[2];
	Rotate(temp, out, (-1)*ang[1]);
	end1[0] = out[0];
	end1[2] = out[1];

	// Rotation along z axis
	temp[0] = end1[0];
	temp[1] = end1[1];
	Rotate(temp, out, ang[2]);
	end1[0] = out[0];
	end1[1] = out[1];

	// Rotation along x axis.
	temp[0] = end2[1];
	temp[1] = end2[2];
	Rotate(temp, out, ang[0]);
	end2[1] = out[0];
	end2[2] = out[1];

	// Rotation along y axis
	temp[0] = end2[0];
	temp[1] = end2[2];
	Rotate(temp, out, (-1)*ang[1]);
	end2[0] = out[0];
	end2[2] = out[1];

	// Rotation along z axis
	temp[0] = end2[0];
	temp[1] = end2[1];
	Rotate(temp, out, ang[2]);
	end2[0] = out[0];
	end2[1] = out[1];
}

void Line::Rotate(double vecIn[],double vecOut[], double angDegrees)
{ // This function rotate vecIn "ang" degrees and put in vecOut.
	if(angDegrees != 0.0) // It's to avoid numeric problems.
	{
		double module;
		double angVecIn;
		double angRad;
		angRad = angDegrees * 3.141592654/180;
		module = sqrt(vecIn[0]*vecIn[0] + vecIn[1]*vecIn[1]);
		angVecIn = atan2(vecIn[1],vecIn[0]);
		vecOut[0] = module * cos(angVecIn + angRad);
		vecOut[1] = module * sin(angVecIn + angRad);
	}else
	{
		vecOut[0] = vecIn[0]; vecOut[1] = vecIn[1];
	}
}

void Line::Move(QVector<double> & pos)
{
	end1[0] = end1[0] + pos[0];
	end1[1] = end1[1] + pos[1];
	end1[2] = end1[2] + pos[2];
	end2[0] = end2[0] + pos[0];
	end2[1] = end2[1] + pos[1];
	end2[2] = end2[2] + pos[2];
}

void Line::Reflect(bool x, bool y, bool z)
{
	if (x)
	{
		end1[0] = -end1[0];
		end2[0] = -end2[0];
	}
	if (y)
	{
		end1[1] = -end1[1];
		end2[1] = -end2[1];
	}
	if (z)
	{
		end1[2] = -end1[2];
		end2[2] = -end2[2];
	}
}

QString Line::GetLabel()
{
	return label;
}

int Line::GetTagNumber()
{
	return tagNumber;
}

int Line::GetCardParameter()
{
	return cardParameter;
}

int Line::GetCardParameter1()
{
	return cardParameter1;
}

QVector<double> Line::GetEnd1()
{
	return end1;
}

QVector<double> Line::GetEnd2()
{
	return end2;
}

double Line::GetWidth()
{
	return width;
}

double Line::GetColor()
{
	return color;
}

double Line::CalculateMaxModule()
{
	double module, maxModule;
	maxModule = 0.000001;						// It'll be modified for some end[].
	module = sqrt(end1[0]*end1[0]+end1[1]*end1[1]+end1[2]*end1[2]);
	if(module>maxModule)
		maxModule = module;
	module = sqrt(end2[0]*end2[0]+end2[1]*end2[1]+end2[2]*end2[2]);
	if(module>maxModule)
		maxModule = module;
	return module;

}
