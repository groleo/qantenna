/***************************************************************************
 *   Copyright (C) 2007 by Pablo Odorico                                   *
 *   pablo.odorico@gmail.com                                               *
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

#include "gl.h"
#include "vbo.h"

VBO::VBO(bool newIndexed, GLenum newRenderMode)
{
	indexed= newIndexed;
	loaded= false;
	setRenderMode(newRenderMode);
}

VBO::~VBO()
{
	end();
}

/*****************************************************
	Add elements
******************************************************/

void VBO::addVertex(const Vec3 &vec)
{
	// Check in case the VBO was alredy loaded
	if(loaded) return;

	vertexArray.append(vec.x);
	vertexArray.append(vec.y);
	vertexArray.append(vec.z);
}

void VBO::addVertex(const float &x, const float &y, const float &z)
{
	// Check in case the VBO was alredy loaded
	if(loaded) return;

	vertexArray.append(x);
	vertexArray.append(y);
	vertexArray.append(z);
}

void VBO::addNormal(const Vec3 &vec)
{
	// Check in case the VBO was alredy loaded
	if(loaded) return;

	normalArray.append(vec.x);
	normalArray.append(vec.y);
	normalArray.append(vec.z);
}

void VBO::addNormal(const float &x, const float &y, const float &z)
{
	// Check in case the VBO was alredy loaded
	if(loaded) return;

	normalArray.append(x);
	normalArray.append(y);
	normalArray.append(z);
}

void VBO::addColor(const QColor &col)
{
	// Check in case the VBO was alredy loaded
	if(loaded) return;

	colorArray.append(col.red());
	colorArray.append(col.green());
	colorArray.append(col.blue());
	colorArray.append(col.alpha());
}

void VBO::addColor(const GLubyte &r, const GLubyte &g, const GLubyte &b, const GLubyte &a)
{
	// Check in case the VBO was alredy loaded
	if(loaded) return;

	colorArray.append(r);
	colorArray.append(g);
	colorArray.append(b);
	colorArray.append(a);
}

void VBO::addIndex(const GLuint &index)
{
	// Check in case the VBO was alredy loaded
	if(loaded) return;

	if(indexed)
		indexArray.append(index);
}

/*****************************************************
	VBO operations
******************************************************/

void VBO::clear()
{
	vertexArray.clear();
	normalArray.clear();
	colorArray.clear();
	if(indexed)
		indexArray.clear();
}

int VBO::size()
{
	return
		vertexArray.count() * sizeof(GLfloat) +
		normalArray.count() * sizeof(GLfloat) +
		colorArray.count() * sizeof(GLubyte) +
		indexArray.count() * sizeof(GLuint);
}

void VBO::setUp()
{
	// Check in case the VBO is already on memory
	if(loaded) return;

	// Generate buffers
	glGenBuffers(bufferSize-(indexed)?0:1, buffers);

	bindBuffers();

	// Copy Data, using GL_STATIC_DRAW
	// Hopefully the data will end up in the video memory
	// NOTICE data
	glBufferData(GL_ARRAY_BUFFER, vertexArray.count() * sizeof(GLfloat),
				vertexArray.data(), GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, normalArray.count() * sizeof(GLfloat),
				normalArray.data(), GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, colorArray.count() * sizeof(GLubyte),
				normalArray.data(), GL_STATIC_DRAW);

	if(indexed) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArray.count() * sizeof(GLuint),
					indexArray.data(), GL_STATIC_DRAW);
	}

	// Data has been copied, we can get rid of the data stored locally
	clear();

	loaded= true;
}

void VBO::end()
{
	// Check in case the VBO wasn't uploaded
	if(!loaded) return;

	glDeleteBuffers(bufferSize-(indexed)?0:1, buffers);

	loaded= false;
}

void VBO::draw()
{
	// Check in case the VBO wasn't uploaded
	if(!loaded) return;

	bindBuffers();

	// Pointers
	glVertexPointer(3, GL_FLOAT, 0, vertexArray.data());
	glNormalPointer(GL_FLOAT, 0, normalArray.data());
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colorArray.data());
	glIndexPointer(GL_UNSIGNED_INT, 0, indexArray.data());

	if(indexed)
		// Draw elements according to indexArray
		glDrawElements(renderMode, vertexArray.count()/3, GL_UNSIGNED_INT, indexArray.data());
	else
		// Draw all the elements
		glDrawArrays(renderMode, 0, vertexArray.count()/3);
}

void VBO::bindBuffers()
{
	// Check in case the VBO wasn't uploaded
	if(!loaded) return;

	glBindBuffer(GL_ARRAY_BUFFER, buffers[vertexIndex]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[normalIndex]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[colorIndex]);
	if(indexed)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[indexIndex]);
}

/*****************************************************
	GET/SET
******************************************************/

bool VBO::getIndexed()
{
	return indexed;
}

void VBO::setRenderMode(const GLenum &mode)
{
	if(	mode==GL_LINES || mode==GL_LINE_STRIP || mode==GL_LINE_LOOP ||
		mode==GL_TRIANGLES || mode==GL_TRIANGLE_STRIP || mode==GL_TRIANGLE_FAN ||
		mode==GL_QUADS || mode==GL_QUAD_STRIP ||
		mode==GL_POLYGON || mode==GL_POINTS)

		renderMode= mode;
	else
		renderMode= GL_TRIANGLE_STRIP;
}

GLenum VBO::getRenderMode()
{
	return renderMode;
}

bool VBO::getLoaded()
{
	return loaded;
}
