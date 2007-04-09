#include "gl.h"

#include <GL/gl.h>
#include <QDebug>
#include <QString>

void GL::vertex(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	glVertex4f(x, z, -y, w);
}

void GL::translate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glTranslatef(x, z, -y);
}

void GL::rotate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glRotatef(x, 1,0,0);
	glRotatef(z, 0,1,0);
	glRotatef(y, 0,0,1);
}

void GL::scale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glScalef(x, z, y);
}

void GL::color(const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a)
{
	glColor4f(r, g, b, a);
}

GLenum GL::checkError(const QString &file, const int &line)
{
	GLenum glErr = glGetError();
	while(glErr != GL_NO_ERROR) {
		const GLubyte* sError = gluErrorString(glErr);

		qDebug() << "** GL Error" << endl <<
		"  Number: " << glErr << endl <<
		"  Message:" << sError << endl <<
		"  File:   " << file << endl <<
		"  Line:   " << line;

		glErr = glGetError();
	}
	return glErr;
}

