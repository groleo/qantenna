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
#ifndef VERTEXVertexMatrix_H
#define VERTEXVertexMatrix_H

#include "point4f.h"

/**
	This class holds a VertexMatrix of row x columns size.
	The VertexMatrix is accesed with values between (0..row-1, 0..column-1).
 */

class VertexMatrix
{

public:
	/// Creates a dimension x dimension VertexMatrix
	VertexMatrix(int dimension);
	VertexMatrix(int rows, int columns );
	~VertexMatrix();

	Point4F getValue( int row, int column ) const;
	void setValue( int row, int column, Point4F value );
	int getRows() const;
	int getColumns() const;

	void debug() const;

private:
	Point4F * array;
	int rowCount;
	int columnCount;
};
#endif // VERTEXVertexMatrix_H
