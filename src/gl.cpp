#include "gl.h"

#include <GL/glew.h>
#include <QDebug>
#include <QString>

void GL::vertex(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glVertex3f(x, z, -y);
}

void GL::vertex(const Vec3 &vec)
{
	glVertex3f(vec.x, vec.z, -vec.y);
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

void GL::color(const Vec3 &vec, const GLfloat &a)
{
	glColor4f(vec.x, vec.y, vec.z, a);
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

