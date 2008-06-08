#include "gl.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <QDebug>
#include <QString>

namespace GL {

void vertex(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glVertex3f(x, z, -y);
}

void vertex(const Vec3 &vec)
{
	glVertex3f(vec.x, vec.z, -vec.y);
}

void translate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glTranslatef(x, z, -y);
}

void rotate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glRotatef(x, 1,0,0);
	glRotatef(z, 0,1,0);
	glRotatef(y, 0,0,1);
}

void scale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	glScalef(x, z, y);
}

void color(const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a)
{
	glColor4f(r, g, b, a);
}

void color(const Vec3 &vec, const GLfloat &a)
{
	glColor4f(vec.x, vec.y, vec.z, a);
}

GLenum checkError(const QString &file, const int &line)
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

void useVBO(bool enable)
{
	if(enable) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_INDEX_ARRAY);
	} else {
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
	}
}

}
