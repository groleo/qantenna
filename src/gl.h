/***************************************************************************
 *   Copyright (C) 2006 by Pablo Odorico                                   *
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

#ifndef GL_H
#define GL_H

#include <GL/glew.h>
#include <QString>

#include "vec3.h"

#ifndef CHECK_GL_ERROR
	#define CHECK_GL_ERROR() GL::checkError(__FILE__, __LINE__)
#endif

namespace GL {

	void vertex(const GLfloat &x, const GLfloat &y, const GLfloat &z);
	void vertex(const Vec3 &vec);

	void translate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
	void rotate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
	void scale(const GLfloat &x, const GLfloat &y, const GLfloat &z);

	void color(const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a=1);
	void color(const Vec3 &vec, const GLfloat &a=1);

	GLenum checkError(const QString &file, const int &line);

	void useVBO(bool enable);
};

#endif
