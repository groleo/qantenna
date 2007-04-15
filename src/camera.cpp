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

#include <iostream>
#include <cmath>

#include "camera.h"
#include "gl.h"

#define M_PI_180	0.017453292
#define COS(a)		cos((a)*M_PI_180)
#define SIN(a)		sin((a)*M_PI_180)
#define ASIN(v)		(asin(v)/M_PI_180)
#define ACOS(v)		(acos(v)/M_PI_180)
#define ATAN(v) 	(atan(v)/M_PI_180)
#define ATAN2(v1,v2) (atan2(v1, v2)/M_PI_180)
#define POW2(a)		((a)*(a))

Camera::Camera()
{
	reset();
}

Camera::Camera(GLfloat x, GLfloat y, GLfloat z, GLfloat newNear, GLfloat newFar)
{
	reset();

	xPos= x;
	yPos= y;
	zPos= z;
	// Sync spherical coords given the new {x,y,z}Pos
	sphericalFromPosition();

	nearEnd= newNear;
	farEnd= newFar;
}

Camera::~Camera()
{
}


void Camera::reset()
{
	setPos(0,0,0);
	setRot(0,0,0);
	setLimits(10,10,10, 10);

	// Sets orbital angles and mod from current pos
	alphaOrbit= 60;
	betaOrbit= 315;
	rhoOrbit= 3.2;
	commitSpherical();
	lookAt(0,0,0);

	nearEnd= 0.001;
	farEnd= 50;

	step= 0.01;

	run= false;
}

void Camera::turn(GLfloat dx, GLfloat dy, GLfloat dz)
{
	setXRot(xRot + dx);
	setYRot(yRot + dy);
	setZRot(zRot + dz);
}

void Camera::move(GLfloat angle)
{
	// angle is used to move the camera sideways (A and S keys)
	// without affecting where it's looking at
	bool impy= fmodf(angle, 180)==0;

	float dx= SIN(zRot-angle) * ((impy)?COS(xRot):1);
	float dz= SIN(xRot) * COS(angle);
	float dy= COS(zRot-angle) * ((impy)?COS(xRot):1);

	setXPos(xPos - step * dx);
	setYPos(yPos + step * dy);
	setZPos(zPos + step * dz);
}

void Camera::orbit(GLfloat dAlpha, GLfloat dBeta)
{
	setAlphaOrbit(alphaOrbit+dAlpha);
	setBetaOrbit(betaOrbit+dBeta);
	commitSpherical();
}

void Camera::perspective(GLfloat yFov, GLfloat ratio, GLfloat newNear, GLfloat newFar)
{
	if(newNear!= -1) nearEnd= newNear;
	if(newFar != -1) farEnd= newFar;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(yFov, ratio, nearEnd, farEnd);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::applyPos()
{
	GL::translate(-xPos, -yPos, -zPos);
	//printf("x: %.2f y: %.2f z: %.2f\n", xPos, yPos, zPos);
}

void Camera::applyRot()
{
	GL::rotate(-xRot, -yRot, -zRot);
	//printf("b: %.2f a: %.2f\n", betaOrbit, alphaOrbit);
}


void Camera::lookAt(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat dist= sqrt(POW2(xPos-x)+POW2(yPos-y)+POW2(zPos-z));

	// Safety check
	if(!dist) setXPos(xPos+0.001);

	// We adjust the rotation to look at x,y,z
	setXRot(-ASIN((zPos-z)/dist));
	setYRot(0);
	setZRot(ATAN2(xPos-x, y-yPos));
}

void Camera::sphericalFromPosition()
{
	// Safety check
	if(!yPos) yPos= 0.001;

	// Adjust spherical coords from the current cartesian coordinates
	rhoOrbit = distFromOrigin();
	alphaOrbit= ACOS(zPos/rhoOrbit);
	betaOrbit= 90-ATAN2(xPos,yPos);
}

void Camera::commitSpherical()
{
	// Sets the cartesian coordinates given spherical coordinates
	// http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations
	setXPos(rhoOrbit * SIN(alphaOrbit) * COS(betaOrbit));
	setYPos(rhoOrbit * SIN(alphaOrbit) * SIN(betaOrbit));
	setZPos(rhoOrbit * COS(alphaOrbit));
}

// This should be a template...
GLfloat Camera::limit(GLfloat val, GLfloat min, GLfloat max)
{
	if(val>max) val= max;
	if(val<min) val= min;
	return val;
}

int Camera::limit(int val, int min, int max)
{
	if(val>max) val= max;
	if(val<min) val= min;
	return val;
}

GLfloat Camera::distFromOrigin()
{
	return sqrt(xPos*xPos + yPos*yPos + zPos*zPos);
}

// Set functions
void Camera::setXPos(GLfloat x)
{
	xPos= limit(x, -xMax, xMax);
}
void Camera::setYPos(GLfloat y)
{
	yPos= limit(y, -yMax, yMax);
}
void Camera::setZPos(GLfloat z)
{
	zPos= limit(z, -zMax, zMax);
}
void Camera::setPos(GLfloat x, GLfloat y, GLfloat z)
{
	setXPos(x);
	setYPos(y);
	setZPos(z);
}

void Camera::setXRot(GLfloat xAng)
{
	xRot= fmodf(limit(xAng,-90.0,90.0), 360.0);
}
void Camera::setYRot(GLfloat yAng)
{
	yRot= fmodf(yAng, 360.0);
}
void Camera::setZRot(GLfloat zAng)
{
	zRot= fmodf(zAng, 360.0);
}
void Camera::setRot(GLfloat newXRot, GLfloat newYRot, GLfloat newZRot)
{
	setXRot(newXRot);
	setYRot(newYRot);
	setZRot(newZRot);
}

void Camera::setLimits(GLfloat newX, GLfloat newY, GLfloat newZ, GLfloat newRho)
{
	xMax= newX;
	yMax= newY;
	zMax= newZ;
	rhoMax= newRho;
}
void Camera::setStep(GLfloat newSpeed)
{
	step= newSpeed;
}

void Camera::setRun(bool newRun)
{
	if(newRun) {
		if(!run) step+= runDelta;
	} else {
		if(run) step-= runDelta;
	}
	run= newRun;
}

void Camera::setOrbit(GLfloat newAlpha, GLfloat newBeta, GLfloat newRho)
{
	setAlphaOrbit(newAlpha);
	setBetaOrbit(newBeta);
	setRhoOrbit(newRho);
}

void Camera::setAlphaOrbit(GLfloat alpha)
{
	alphaOrbit= limit(alpha, 0.1, 179.9);
}

void Camera::setBetaOrbit(GLfloat beta)
{
	betaOrbit= fmodf(beta, 360.0);
}

void Camera::setRhoOrbit(GLfloat rho)
{
	rhoOrbit= limit(rho, 0.2, rhoMax);
}

GLfloat Camera::getXPos() const
{
	return xPos;
}

GLfloat Camera::getYPos() const
{
	return yPos;
}

GLfloat Camera::getZPos() const
{
	return zPos;
}

GLfloat Camera::getXRot() const
{
	return xRot;
}

GLfloat Camera::getYRot() const
{
	return yRot;
}

GLfloat Camera::getZRot() const
{
	return zRot;
}

GLfloat Camera::getXMax() const
{
	return xMax;
}

GLfloat Camera::getYMax() const
{
	return yMax;
}

GLfloat Camera::getZMax() const
{
	return zMax;
}

GLfloat Camera::getRhoMax() const
{
	return rhoMax;
}

GLfloat Camera::getAlphaOrbit() const
{
	return alphaOrbit;
}

GLfloat Camera::getBetaOrbit() const
{
	return betaOrbit;
}

GLfloat Camera::getRhoOrbit() const
{
	return rhoOrbit;
}

GLfloat Camera::getNear() const
{
	return nearEnd;
}

GLfloat Camera::getFar() const
{
	return farEnd;
}

GLfloat Camera::getStep() const
{
	return step;
}

bool Camera::getRun() const
{
	return run;
}
