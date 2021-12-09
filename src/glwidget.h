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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "gl.h"
#include "camera.h"
#include "datamanager.h"

#include <QGLWidget>

/**
	This class inherits from QGLWidget, and it is used to diaplay the OGL view
	in the program. It also takes cares of some events, wich it then passes to
	the class camera.
*/
class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget * parent = 0);
	~GLWidget();

	void setFileRender(bool newVal);
	QPixmap snapshot(int width, int height);

	// Grid
	void makeGrid(GLfloat z, GLfloat size, GLfloat radio);
	void renderGrid();

public slots:
	void makeCurrentGLWidget();

signals:
	void RenderSurface();
	void setStatus(QString status, int timeout = 2000);
	void rebuildLists();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	// Mouse/Keyboard input
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent (QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void grabInput();
	void releaseInput();
	/// Number of true elements of movingTo[]
	int movingCount();
	/// make movingTo false
	void stopMoving();

private slots:
	void sceneTimerEvent();

private:
	/// Camera
	Camera camera;

	/// Step for changing camera.rhoOrbit (with the mouse wheel)
	constexpr static const float zoomStep= 0.1;

	/// sceneTimer is used to simulate a fast auto-repeat event and
	/// as a scene timer
	static const int timerDelay = 13;
	QTimer *sceneTimer;
	/// Key state (WDSA)
	static const int movingDirections = 4;
	bool movingTo[movingDirections];

	/// Mouse Grabbing information
	constexpr static const float sensibility= 0.1;
	bool mouseGrabbed;
	/// Did the camera moved while the input was grabbed
	bool movedWhileGrabbed;
	QPoint grabPos;
	QPoint lastPos;

	/// A list index for the grid
	GLuint gridList;

	/// If true, initializeGL will emit rebuildLists. This is needed given
	/// that QGLWidget::renderPixmaps creates a new QGLContext
	bool fileRender;
};

#endif // GLWIDGET_H

