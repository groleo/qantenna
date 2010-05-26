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
#include "patch.h"
#include <math.h>

Patch::Patch()
{
	tagNumber = 0;

	end1.append(0.0);
	end1.append(0.0);
	end1.append(0.0);

	end2.append(0.0);
	end2.append(0.0);
	end2.append(0.0);

	end3.append(0.0);
	end3.append(0.0);
	end3.append(0.0);

	end4.append(0.0);
	end4.append(0.0);
	end4.append(0.0);
}

Patch::Patch(QString newLabel, QVector<double> newEnd1, QVector<double> newEnd2,
             QVector<double> newEnd3, QVector<double> newEnd4, int newTagNumber,
             int newCardParameter, int newCardParameter1)
{
	label = newLabel;
	end1 = newEnd1;
	end2 = newEnd2;
	end3 = newEnd3;
	end4 = newEnd4;

	tagNumber = newTagNumber;
	cardParameter = newCardParameter;
	cardParameter1 = newCardParameter1;
}

Patch::~Patch()
{
}

void Patch::SetLabel( QString newLabel)
{
	label = newLabel;
}

void Patch::SetTagNumber( int newTagNumber)
{
	tagNumber = newTagNumber;
}

void Patch::SetEnd1( double x, double y, double z)
{
	end1[0] = x;
	end1[1] = y;
	end1[2] = z;
}

void Patch::SetEnd2( double x, double y, double z)
{
	end2[0] = x;
	end2[1] = y;
	end2[2] = z;
}

void Patch::SetEnd3( double x, double y, double z)
{
	end3[0] = x;
	end3[1] = y;
	end3[2] = z;
}

void Patch::SetEnd4( double x, double y, double z)
{
	end4[0] = x;
	end4[1] = y;
	end4[2] = z;
}

void Patch::SetWidth( double newWidth)
{
	width = newWidth;
}

void Patch::SetColor( double newColor)
{
	color = newColor;
}

void Patch::SetCardParameter(int newCardParameter)
{
	cardParameter = newCardParameter;
}

void Patch::SetCardParameter1(int newCardParameter)
{
	cardParameter1 = newCardParameter;
}

void Patch::Rotate(QVector<double> & ang)
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

	// Rotation along z axis.
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

	// Rotation along y axis.
	temp[0] = end2[0];
	temp[1] = end2[2];
	Rotate(temp, out, (-1)*ang[1]);
	end2[0] = out[0];
	end2[2] = out[1];

	// Rotation along z axis.
	temp[0] = end2[0];
	temp[1] = end2[1];
	Rotate(temp, out, ang[2]);
	end2[0] = out[0];
	end2[1] = out[1];

	// Rotation along x axis.
	temp[0] = end3[1];
	temp[1] = end3[2];
	Rotate(temp, out, ang[0]);
	end3[1] = out[0];
	end3[2] = out[1];

	// Rotation along y axis.
	temp[0] = end3[0];
	temp[1] = end3[2];
	Rotate(temp, out, (-1)*ang[1]);
	end3[0] = out[0];
	end3[2] = out[1];

	// Rotation along z axis.
	temp[0] = end3[0];
	temp[1] = end3[1];
	Rotate(temp, out, ang[2]);
	end3[0] = out[0];
	end3[1] = out[1];

	// Rotation along x axis.
	temp[0] = end4[1];
	temp[1] = end4[2];
	Rotate(temp, out, ang[0]);
	end4[1] = out[0];
	end4[2] = out[1];

	// Rotation along y axis.
	temp[0] = end4[0];
	temp[1] = end4[2];
	Rotate(temp, out, (-1)*ang[1]);
	end4[0] = out[0];
	end4[2] = out[1];

	// Rotation along z axis.
	temp[0] = end4[0];
	temp[1] = end4[1];
	Rotate(temp, out, ang[2]);
	end4[0] = out[0];
	end4[1] = out[1];
}

void Patch::Rotate(double vecIn[],double vecOut[], double angDegrees)
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
	}
	else
	{
		vecOut[0] = vecIn[0];
		vecOut[1] = vecIn[1];
	}
}

void Patch::Move(QVector<double> & pos)
{
	end1[0] = end1[0] + pos[0];
	end1[1] = end1[1] + pos[1];
	end1[2] = end1[2] + pos[2];
	end2[0] = end2[0] + pos[0];
	end2[1] = end2[1] + pos[1];
	end2[2] = end2[2] + pos[2];
	end3[0] = end3[0] + pos[0];
	end3[1] = end3[1] + pos[1];
	end3[2] = end3[2] + pos[2];
	end4[0] = end4[0] + pos[0];
	end4[1] = end4[1] + pos[1];
	end4[2] = end4[2] + pos[2];
}

void Patch::Reflect(bool x, bool y, bool z)
{
	if (x)
	{
		end1[0] = -end1[0];
		end2[0] = -end2[0];
		end3[0] = -end3[0];
		end4[0] = -end4[0];
	}
	if (y)
	{
		end1[1] = -end1[1];
		end2[1] = -end2[1];
		end3[1] = -end3[1];
		end4[1] = -end4[1];
	}
	if (z)
	{
		end1[2] = -end1[2];
		end2[2] = -end2[2];
		end3[2] = -end3[2];
		end4[2] = -end4[2];
	}
}

QString Patch::GetLabel()
{
	return label;
}

int Patch::GetTagNumber()
{
	return tagNumber;
}

int Patch::GetCardParameter()
{
	return cardParameter;
}

int Patch::GetCardParameter1()
{
	return cardParameter1;
}

QVector<double> Patch::GetEnd1()
{
	return end1;
}

QVector<double> Patch::GetEnd2()
{
	return end2;
}

QVector<double> Patch::GetEnd3()
{
	return end3;
}

QVector<double> Patch::GetEnd4()
{
	return end4;
}

double Patch::GetWidth()
{
	return width;
}

double Patch::GetColor()
{
	return color;
}

double Patch::CalculateMaxModule()
{
	double module, maxModule;
	maxModule = 0.000001;						// It'll be modified for some end[].
	module = sqrt(end1[0]*end1[0]+end1[1]*end1[1]+end1[2]*end1[2]);
	if(module>maxModule)
		maxModule = module;
	module = sqrt(end2[0]*end2[0]+end2[1]*end2[1]+end2[2]*end2[2]);
	if(module>maxModule)
		maxModule = module;
	module = sqrt(end3[0]*end3[0]+end3[1]*end3[1]+end3[2]*end3[2]);
	if(module>maxModule)
		maxModule = module;
	module = sqrt(end4[0]*end4[0]+end4[1]*end4[1]+end4[2]*end4[2]);
	if(module>maxModule)
		maxModule = module;
	return module;
}
