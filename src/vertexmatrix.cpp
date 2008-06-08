/***************************************************************************
 *   Copyright (C) 2005-2007 by Lisandro Damián Nicanor Pérez Meyer        *
 *   perezmeyer@gmail.com                                                  *
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
#include <QDebug>
#include <float.h>
#include "vertexmatrix.h"

VertexMatrix::VertexMatrix( int dimension )
{
	rowCount = dimension;
	columnCount = dimension;
	array = new Point4F[rowCount * columnCount];
}

VertexMatrix::VertexMatrix( int rows, int columns )
{
	rowCount = rows;
	columnCount = columns;
	array = new Point4F[rowCount * columnCount];
}

VertexMatrix::~VertexMatrix()
{
  delete[] array;
}

Point4F VertexMatrix::getValue(int row, int column) const
{
  return array[(row * columnCount) + column];
}

void VertexMatrix::setValue(int row, int column, Point4F value)
{
  array[(row * columnCount) + column] = value;
}

int VertexMatrix::getRows() const
{
	return rowCount;
}

int VertexMatrix::getColumns() const
{
	return columnCount;
}

void VertexMatrix::debug() const
{
	for(int i=0; i<rowCount; i++)
	{
		for(int j=0; j<columnCount; j++)
		{
			qDebug() << getValue(i,j);
		}
		printf("\n");
	}
}

