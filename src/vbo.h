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

#ifndef VBOL_H
#define VBO_H

#include "gl.h"
#include "vec3.h"

#include <QVector>
#include <QColor>

/**
	OpenGL Vertex Buffer Object abstraction

	Data storage:
		XYZ GLfloat vertex array
		XYZ GLfloat normal array
		RGBA GLubyte color array

	usesIndexes: If true, addIndex is enabled and glDrawElements will be used
		for rendering instead of glDrawArray instead of glDrawArrays (draws all
		the	the array)

	Defualt render mode: GL_TRIANGLE_STRIP
*/
class VBO
{
public:
	VBO(bool newIndexed=true, GLenum newRenderMode=GL_TRIANGLE_STRIP);
	~VBO();

	/// Appends the components of vec to vertexArray
	void addVertex(const Vec3 &vec);
	/// Appends x, y and z to vertexArray
	void addVertex(const GLfloat &x, const GLfloat &y, const GLfloat &z);

	/// Appends the components of vec to normalArray
	void addNormal(const Vec3 &vec);
	/// Appends x, y and z to normalArray
	void addNormal(const GLfloat &x, const GLfloat &y, const GLfloat &z);

	/// Appends the components of col to colorArray
	void addColor(const QColor &col);
	/// Appends r, g, b, and a to colorArray
	void addColor(const GLubyte &r, const GLubyte &g, const GLubyte &b, const GLubyte &a);

	/// Appends index to indexArray
	void addIndex(const GLuint &index);

	/// Empties the internal arrays
	void clear();

	/// Approx. size in bytes
	int size();

	void setUp();
	void end();
	void draw();

	/// Returns indexed
	bool getIndexed();
	/// Was this VBO uploaded to memory?
	bool getLoaded();

	/// Sets the render mode, if mode is not valid, use GL_TRIANGLE_STRIP
	void setRenderMode(const GLenum &mode);
	/// Returns the current render mode
	GLenum getRenderMode();

private:

	/// Used to bind the VBO buffers
	void bindBuffers();

	/// Whether indexArray is going to be used or not
	bool indexed;

	/// Whether the buffers were created and loaded into memory
	bool loaded;

	/// Rendermode: GL_POINTS, GL_QUADS, etc.
	GLenum renderMode;

	/// Amount of buffers (using vertex, normal and color)
	static const int bufferSize = 4;
	/// Buffers OpenGL IDs
	GLuint buffers[bufferSize];
	/// Indices of buffers[]
	enum {
		vertexIndex= 0,
		normalIndex= 1,
		colorIndex = 2,
		indexIndex = 3
	};

	/// Vertices
	QVector<GLfloat> vertexArray;
	/// Normals
	QVector<GLfloat> normalArray;
	/// Colors
	QVector<GLubyte> colorArray;
	/// Indexes
	QVector<GLuint>  indexArray;
};

#endif
