/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
 *   Lisandro Damián Nicanor Pérez Meyer - perezmeyer en/at gmail.com      *
 *   Gustavo González - gonzalgustavo en/at gmail.com                      *
 *   Pablo Odorico  pablo.odorico en/at gmail.com                          *
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
#include "glwidget.h"
#include "camera.h"
#include "mmath.h"

#include <QtGui>
#include <QtOpenGL>
#include <cmath>

GLWidget::GLWidget(QWidget * parent)
	: QGLWidget(parent)
{
	mouseGrabbed= false;
	movedWhileGrabbed= false;

	// movingTo initialization
	stopMoving();

	// sceneTimer is connected to sceneTimerEvent (private slot)
	sceneTimer= new QTimer(this);
	connect(sceneTimer, SIGNAL(timeout()), this, SLOT(sceneTimerEvent()));

	makeGrid(0.0,0.1,2.0);

	fileRender= false;
}

GLWidget::~GLWidget()
{
	// We erase the lists
	glDeleteLists(gridList, 1);

}

void GLWidget::setFileRender(bool newVal)
{
	fileRender= newVal;
}

void GLWidget::makeCurrentGLWidget()
{
	makeCurrent();
}

void GLWidget::initializeGL()
{
// 	glEnable(GL_LIGHTING);
// 	glEnable(GL_LIGHT0);

	setAutoBufferSwap(false);

	// We do not want blending by now
	glDisable(GL_BLEND);
	// We do not want depth test by now
	glDisable(GL_DEPTH_TEST);

	/**
		FIXME
		If the line below is uncommented, the program crashes. I could not trace
		the problem of the crash.
		If you happen to know where it it, please, let me know.
		Lisandro.
	*/
// 	glEnableClientState(GL_NORMAL_ARRAY);

	if(fileRender) {
		emit rebuildLists();
	}
}

void GLWidget::paintGL()
{
/*
	static QTime time0= QTime::currentTime();
	static GLint frames= 0;
*/
	glClearColor(135.0/255, 135.0/255, 135.0/255, 1);

	// Clean
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// We save the state
	glPushMatrix();

	// Camera transformations:
	// rotation
	camera.applyRot();
	// position
	camera.applyPos();

	glTranslated(0, 0, 0);

	// We tell the Datamanager that it must render
	emit RenderSurface();

	glPopMatrix();
	swapBuffers();

/*
	// FPS calc
	frames++;
	QTime time= QTime::currentTime();
	float dif= time0.msecsTo(time);
	if(dif >= 2000) {
		qDebug() << frames/(dif/1000.0) << "fps.";
		time0= time;
		frames= 0;
	}
*/
}

void GLWidget::resizeGL(int width, int height)
{
	GLfloat ratio;

	if(!height)
		height=1;
	ratio = (GLfloat)width/height;

	glViewport(0, 0, (GLint)width, (GLint)height);

	// Camera class handles perspective
	camera.perspective(45, ratio);
}

int GLWidget::movingCount()
{
	int i, keysPressed= 0;

	for(i=0; i<movingDirections; i++)
		if(movingTo[i]) keysPressed++;

	return keysPressed;
}

void GLWidget::stopMoving()
{
	for(int i=0; i<movingDirections; i++)
		movingTo[i]= false;
	camera.setRun(false);
}

void GLWidget::grabInput()
{
	if(mouseGrabbed) return;

	// Stores grab position
	grabPos = lastPos = QCursor::pos();
	// Grabs keyboard and mouse hiding the cursor
	grabMouse(Qt::BlankCursor);
	grabKeyboard();
	// Calls mouseMoveEvent even the cursor is not
	// over the widget
	setMouseTracking(true);

	mouseGrabbed = true;

	sceneTimer->start(timerDelay);
}

void GLWidget::releaseInput()
{
	if(!mouseGrabbed) return;

	QCursor::setPos(grabPos);
	releaseMouse();
	releaseKeyboard();
	setMouseTracking(false);

	sceneTimer->stop();
	stopMoving();

	mouseGrabbed = false;
}

void GLWidget::sceneTimerEvent()
{
	int moveCount= movingCount();

	if(moveCount==1) {
		// 0 1 2 3
		if(movingTo[0]) camera.move(0);
		if(movingTo[1]) camera.move(90);
		if(movingTo[2]) camera.move(180);
		if(movingTo[3]) camera.move(270);
	} else {
		// Diagonals
		if(movingTo[0] && movingTo[1]) camera.move(45);
		if(movingTo[1] && movingTo[2]) camera.move(135);
		if(movingTo[2] && movingTo[3]) camera.move(225);
		if(movingTo[3] && movingTo[0]) camera.move(315);
	}

	// The camera changed position
	if(moveCount) movedWhileGrabbed= true;

	// Only updateGL when needed
	//update();
	paintGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	// Ignore autoRepeat key events
	if(event->isAutoRepeat()) return;

	// Set a new moving direction
	switch(event->key()) {
		case Qt::Key_W:
		case Qt::Key_Up:
			movingTo[0]= true;
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			movingTo[1]= true;
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			movingTo[2]= true;
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			movingTo[3]= true;
			break;
		case Qt::Key_Shift:
			camera.setRun(true);
			break;
		case Qt::Key_Return:
			camera.lookAt(0,0,0);
			break;
		case Qt::Key_Escape:
			releaseInput();
			break;
	}
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	// Ignore autoRepeat key events
	if(event->isAutoRepeat())
		return;

	// Set a new moving direction
	switch(event->key()) {
		case Qt::Key_W:
		case Qt::Key_Up:
			movingTo[0]= false;
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			movingTo[1]= false;
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			movingTo[2]= false;
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			movingTo[3]= false;
			break;
		case Qt::Key_Shift:
			camera.setRun(false);
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::RightButton) {
		if(mouseGrabbed)
			releaseInput();
		else {
			emit setStatus(tr("Exploration mode: Use W, S, A and D keys to go forward, backward or move sideways"));
			grabInput();
		}
	}

	if(event->buttons() & Qt::MidButton) {
		camera.reset();

		if(!mouseGrabbed) update();
	}

	lastPos= event->globalPos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	// Needed to ignore evets emited by QCursor::setPos
	// when the mouse is captured
	if(event->globalPos() == grabPos)
		return;

	int dx = event->globalX() - lastPos.x();
	int dy = event->globalY() - lastPos.y();

	if(mouseGrabbed) {
		// Rotates camera
		dx = event->globalX() - grabPos.x();
		dy = event->globalY() - grabPos.y();

		// mouse sensibility could by adjusted from here...
		// (replacing /10 for *sensibility)
		camera.turn(-dy*sensibility, 0, -dx*sensibility);

		// Return the cursor to the grabPosition so it
		// never reaches the edge of the screen
		QCursor::setPos(grabPos);

		// glWidget will be updated by the timer
	} else if(event->buttons()&Qt::LeftButton) {

		emit setStatus(tr("Orbital mode: Move around the antenna by dragging it"));

		// Orbits camera
		dx = event->globalX() - lastPos.x();
		dy = event->globalY() - lastPos.y();

		if(movedWhileGrabbed) {
			// Update spherical coords from the new position
			camera.sphericalFromPosition();
			//camera.commitSpherical();
			movedWhileGrabbed= false;
		}
		// Orbit position
		camera.orbit(-0.37 * dy, -0.37 * dx);
		// Look at the origin
		camera.lookAt(0,0,0);

		// lastPos is used to calculate dx and dy
		lastPos = event->globalPos();

		// Only updateGL when needed
		update();
	}

}

void GLWidget::wheelEvent(QWheelEvent *event)
{
	if(!mouseGrabbed) {
		camera.lookAt(0,0,0);
		if(event->delta()>0)
			camera.setRhoOrbit(camera.getRhoOrbit()-zoomStep);
		else
			camera.setRhoOrbit(camera.getRhoOrbit()+zoomStep);
		camera.commitSpherical();
		update();
	}
}

QPixmap GLWidget::snapshot(int width, int height)
{
	// renderPixmap will call initializeGL, resizeGL and paintGL in a
	// new QGLContext. Since fileRender=true, initializeGL will
	// rebuild the display lists (delete de currents and generate new ones)
	fileRender= true;
	QPixmap pixmap= renderPixmap(width, height);
	fileRender= false;
	// new lists need to be generated for the original context
	emit rebuildLists();
	return pixmap;
}

void GLWidget::makeGrid(GLfloat z, GLfloat size, GLfloat radio)
{
	makeCurrent();

	if(glIsList(gridList)) glDeleteLists(gridList, 1);
	gridList = glGenLists(1);

	if(gridList == 0)
	{
		qDebug() << tr("QAntenna - DataManager");
		qDebug() << tr("I can not create the OpenGL list for the grid");
		return;
	}

	GLfloat x, y;

	glNewList(gridList, GL_COMPILE);
	glBegin(GL_LINES);
		GL::color(.3, .3, .3);
		for(x=-radio; x<radio+size; x+=size) {
			GL::vertex(x, -radio, z);
			GL::vertex(x, radio, z);
		}

		for(y=-radio; y<radio+size; y+=size) {
			GL::vertex(-radio, y, z);
			GL::vertex(radio, y, z);
		}

		// Ejes
		// x
		GL::color(.5, 0, 0);
		GL::vertex(0, 0, 0);
		GL::color(1, .4, .4);
		GL::vertex(radio/2, 0, 0);
		// y
		GL::color(0, .5, 0);
		GL::vertex(0, 0, 0);
		GL::color(.4, 1, .4);
		GL::vertex(0, radio/2, 0);
		// z
		GL::color(0, 0, .5);
		GL::vertex(0, 0, 0);
		GL::color(.4, .4, 1);
		GL::vertex(0, 0, radio/2);

		// Label X
		GL::color(1, 0, 0);
		GL::vertex(radio/2+0.1+ -.04, -.04, 0);
		GL::vertex(radio/2+0.1+  .04,  .04, 0);
		GL::vertex(radio/2+0.1+  .04, -.04, 0);
		GL::vertex(radio/2+0.1+ -.04,  .04, 0);
		// Label Y
		GL::color(0, 1, 0);
		GL::vertex(-.04, radio/2+0.1+  .04, 0);
		GL::vertex(   0, radio/2+0.1+    0, 0);
		GL::vertex( .04, radio/2+0.1+  .04, 0);
		GL::vertex(-.04, radio/2+0.1+ -.04, 0);
		// Label Z
		GL::color(0, 0, 1);
		GL::vertex(0, -.04, radio/2+0.1+  0.04);
		GL::vertex(0,  .04, radio/2+0.1+  0.04);
		GL::vertex(0,  .04, radio/2+0.1+ -0.04);
		GL::vertex(0, -.04, radio/2+0.1+ -0.04);
		GL::vertex(0, -.04, radio/2+0.1+ -0.04);
		GL::vertex(0,  .04, radio/2+0.1+  0.04);


	glEnd();
	glEndList();
}

void GLWidget::renderGrid()
{
	glLineWidth(1);
	glCallList(gridList);
}

