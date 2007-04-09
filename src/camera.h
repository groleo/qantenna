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

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <QMatrix>

/**
	Camera class

	This class doesn't update the scene (updateGL in GLWidget), but
	contains camera-related information and applies OpenGL transformations
**/
class Camera {

public:
	Camera();
	Camera(GLfloat x, GLfloat y, GLfloat z, GLfloat newNear, GLfloat newFar);
	~Camera();


	/// Sets angles relative to current values (setRot assigns new values)
	void turn(GLfloat dx, GLfloat dy, GLfloat dz);
	/// Sets position relative to current values (setPos assigns new values)
	/// it simulates a Half-Life kind of camera movement
	void move(GLfloat angle);
	/// Sets spherical angles relative to current values (setOrbit assigns new values)
	void orbit(GLfloat dAlpha, GLfloat dBeta);

	/// Calls gluPerspective and optionally sets near and far
	void perspective(GLfloat yFov= 45, GLfloat ratio= 4.0/3.0, GLfloat newNear=-1, GLfloat newFar=-1);

	/// Calls glTranslatef using -{x,y,z}Pos
	void applyPos();
	/// Calls glRotatef using -{x,y,z}Rot
	void applyRot();


	/// Mathematical implementation of gluLookAt (doesn't make OpenGL calls)
	void lookAt(GLfloat x=0, GLfloat y=0, GLfloat z=0);
	/// Adjust spherical coords from the current cartesian coordinates
	void sphericalFromPosition();
	/// Sets the cartesian coordinates given the current spherical coordinates
	void commitSpherical();

	/// Resets values
	void reset();

	/// |Position|
	GLfloat distFromOrigin();

	/// Set
	void setPos(GLfloat x, GLfloat y, GLfloat z);
	void setXPos(GLfloat x);
	void setYPos(GLfloat y);
	void setZPos(GLfloat z);

	void setRot(GLfloat newXRot, GLfloat newYRot, GLfloat newZRot);
	void setXRot(GLfloat xAng);
	void setYRot(GLfloat yAng);
	void setZRot(GLfloat zAng);

	void setOrbit(GLfloat newAlpha, GLfloat newBeta, GLfloat newRho);
	// Use commitSpherical() to commit changes to {x,y,z}Pos
	void setAlphaOrbit(GLfloat alpha);
	void setBetaOrbit(GLfloat beta);
	void setRhoOrbit(GLfloat rho);

	void setLimits(GLfloat newX, GLfloat newY, GLfloat newZ, GLfloat newRho);
	void setStep(GLfloat newSpeed);

	void setRun(bool newRun);

	/// Get
	GLfloat getXPos() const;
	GLfloat getYPos() const;
	GLfloat getZPos() const;

	GLfloat getXRot() const;
	GLfloat getYRot() const;
	GLfloat getZRot() const;

	GLfloat getXMax() const;
	GLfloat getYMax() const;
	GLfloat getZMax() const;
	GLfloat getRhoMax() const;

	GLfloat getAlphaOrbit() const;
	GLfloat getBetaOrbit() const;
	GLfloat getRhoOrbit() const;

	GLfloat getNear() const;
	GLfloat getFar() const;
	GLfloat getStep() const;

	bool getRun() const;

	/// Sets val between min and max
	static GLfloat limit(GLfloat val, GLfloat min, GLfloat max);
	static int limit(int val, int min, int max);

private:
	/// Real coords
	/// Camera Azimuth
	GLfloat xPos;
	/// Camera elevation above the horizon
	GLfloat yPos;
	/// Almost never used, but supported
	GLfloat zPos;

	/// Rotation
	GLfloat xRot, yRot, zRot;

	/// Position limits: [-max, max]
	GLfloat xMax, yMax, zMax, rhoMax;

	/// Minimum and Maximum viewing distance
	GLfloat nearEnd;
	GLfloat farEnd;

	/// Moving speed
	GLfloat step;
	bool run;
	static const float runDelta= 0.04;

	/** Camera orbitation around origin, these coords are applied to
		{x,y,z}Rot with commitSpherical()
		Basic idea: http://deslab.mit.edu/DesignLab/courses/13.016/graphics/viewing.html
		http://en.wikipedia.org/wiki/Spherical_coordinates
		theta -> alphaOrbit
		phi -> betaOrbit
		rho -> rhoOrbit
	*/
	GLfloat alphaOrbit, betaOrbit, rhoOrbit;
};

#endif // CAMERA_H
