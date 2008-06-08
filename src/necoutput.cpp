/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
 *   Lisandro Damián Nicanor Pérez Meyer - perezmeyer en/at gmail.com      *
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
#include "necoutput.h"
#include "glwidget.h"

#include <QList>
#include <cmath>
#include <QGLWidget>
#include <float.h>

// Slices and stacks of the spheres
#define SLICES 5
#define STACKS 5

/**
	We should transform the position data to rectangular coordinates,
	so we will perform:

	\f$ x_R = 10^((TotalGain-maxPowerGain)/10)*sin(phi*M_PI/180)*cos(theta*M_PI/180)\f$ \n
	\f$ y_R = 10^((TotalGain-maxPowerGain)/10)*sin(phi*M_PI/180)*sin(theta*M_PI/180)\f$ \n
	\f$ z_R = 10^((TotalGain-maxPowerGain)/10)*cos(theta*M_PI/180)\f$

	Taking into account that OpenGL takes the axis in a different way:

	\f$ X_OGL=10^((TotalGain-maxPowerGain)/10)*cos(phi*M_PI/180)*sin(theta*M_PI/180)\f$
	\f$ Y_OGL=10^((TotalGain-maxPowerGain)/10)*cos(theta*M_PI/180)\f$
	\f$ Z_OGL=(-1)*10^((TotalGain-maxPowerGain)/10)*sin(phi*M_PI/180)*sin(theta*M_PI/180)\f$

	\f$ Total_Gain/maxPowerGain \f$ is done in order to normalize the radiation to the
	maximum gain. Note that they are in dB, and we need them in the linear way.
	Angles are given in decimal degrees, and we need them in radians, so we
	multiplicate by M_PI and divide by 180.
 */

NECOutput::NECOutput(GLWidget * gl, QWidget * parent) : QObject(parent)
{
	glWidget = gl;
	/**
		We set maxPowerGain to DBL_MIN in order that any TotalGain will
		update the value.
		Perhaps there's a better solution for this.
	*/
	maxPowerGain = DBL_MIN;
	dBMinimum = -25.0;
	radius = 0.05;
	alpha = 0.5;

	surfaceEnabled = true;
	spheresEnabled = false;
	meshEnabled = false;
	insideTrianglesEnabled = false;

	ro = 1.0;

	deltaX = 0.0;
	deltaY = 0.0;
	deltaZ = 0.0;

	colorScheme = 0;
}

NECOutput::~NECOutput()
{
	glWidget->makeCurrent();
	//We empty the radiation pattern list
	RadiationPattern * temp;
	for( int i=0; i<radiationPatternList.size(); i++ )
	{
		temp = radiationPatternList.takeFirst();
		delete temp;
	}

	// Delete the vertex matrix
	delete vertexMatrix;
}

void NECOutput::SetRadiationPattern(RadiationPattern * newRadiationPattern)
{
	if(newRadiationPattern->GetTotalGain() > maxPowerGain )
		maxPowerGain = newRadiationPattern->GetTotalGain();
	radiationPatternList.append( newRadiationPattern );
}

void NECOutput::setColorScheme(int theColorScheme)
{
	colorScheme = theColorScheme;
}

void NECOutput::ProcessData()
{
	createMatrix();

	glWidget->makeCurrent();

	quad = gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);

	// We clean all the arrays
	surfaceVertexArray.clear();
	surfaceColorArray.clear();
	surfaceNormalArray.clear();
	meshVertexArray.clear();
	meshColorArray.clear();
	meshNormalArray.clear();
	insideTrianglesVertexArray.clear();
	insideTrianglesColorArray.clear();
	insideTrianglesNormalArray.clear();

	// And we calculate the patterns
	calculateSurface();
	calculateMesh();
	calculateInsideTriangles();
}

void NECOutput::Render()
{
	// We will need blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// We need to do depth testing
	glEnable(GL_DEPTH_TEST);

	// We enable the arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
// 	glEnableClientState(GL_NORMAL_ARRAY);

	// We would render if there is data available
	if(surfaceVertexArray.size() > 1)
	{
		glWidget->makeCurrent();
		glPushMatrix();
		glTranslated(deltaX,deltaY,deltaZ);
		glScaled(ro,ro,ro);
		if(surfaceEnabled)
		{
			// We specify the corrects arrays
			glVertexPointer(3,GL_DOUBLE,0,surfaceVertexArray.data());
			glColorPointer(4,GL_DOUBLE, 0,surfaceColorArray.data());
// 			glNormalPointer(GL_DOUBLE,0,surfaceNormalArray.data());
			// We draw the arrays
			glDrawArrays(GL_TRIANGLE_STRIP,0, surfaceVertexArray.size()/3);
		}
		if(spheresEnabled)
		{
			double x = 0;
			double y = 0;
			double z = 0;
			double R = 0;
			double red = 0;
			double green = 0;
			double blue = 0;
			for(int i=0; i<radiationPatternList.size(); i++)
			{
				// The spheres
				CalculateXYZ(i,x,y,z,R);
				glNormal3d(x,y,z);
				glTranslated(x,y,z);
				calculateColors(i,R,red,green,blue);
				glColor4f(red,green,blue,alpha);
				gluSphere(quad,radius,SLICES,STACKS);
				glTranslated(-x,-y,-z);
			}
		}
		if(meshEnabled)
		{
			glVertexPointer(3,GL_DOUBLE,0,meshVertexArray.data());
			glColorPointer(4,GL_DOUBLE,0,meshColorArray.data());
// 			glNormalPointer(GL_DOUBLE,0,meshNormalArray.data());
			glDrawArrays(GL_LINE_STRIP,0,meshVertexArray.size()/3);
		}
		if(insideTrianglesEnabled)
		{
			glVertexPointer(3,GL_DOUBLE,0,insideTrianglesVertexArray.data());
			glColorPointer(4,GL_DOUBLE,0,insideTrianglesColorArray.data());
// 			glNormalPointer(GL_DOUBLE,0,insideTrianglesNormalArray.data());
			glDrawArrays(GL_TRIANGLE_STRIP,0,insideTrianglesVertexArray.size()/3);
		}
		glPopMatrix();
	}
	// We disable the arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	// We disable blending
	glDisable(GL_BLEND);
	// We disable depth testing
	glDisable(GL_DEPTH_TEST);
}

void NECOutput::setDisplacement(double & x, double & y, double & z)
{
	deltaX = x;
	deltaY = y;
	deltaZ = z;
}

void NECOutput::setDBMinimum(double newDB)
{
	dBMinimum = newDB;
	ProcessData();
}

void NECOutput::setRadius(double newRadius)
{
	radius = newRadius;
}

void NECOutput::setAlpha(double newAlpha)
{
	alpha = newAlpha;
	ProcessData();
}

void NECOutput::setRenderSurface(bool render)
{
	surfaceEnabled = render;
}

void NECOutput::setRenderSpheres(bool render)
{
	spheresEnabled = render;
}

void NECOutput::setRenderMesh(bool render)
{
	meshEnabled = render;
}

void NECOutput::setRenderInsideTriangles(bool render)
{
	insideTrianglesEnabled = render;
}

void NECOutput::setRo(double newRo)
{
	if(newRo <= 0)
		ro = 0.1;
	else
		ro = newRo;
	Render();
}

void NECOutput::calculateColors(int position, const double R, double & red,
                                double & green, double & blue)
{
	red = 0.0;
	green = 0.0;
	blue = 0.0;

	if(colorScheme == 0)
	{
		if(R > 0.5)
		{
			red = (2*R)-1;
			green = (-2*R)+2;
		}
		else
		{
			green = 2*R;
			blue = (-2*R)+1;
		}
	}
	else if(colorScheme == 1)
	{
		if(radiationPatternList.at(position)->GetPolarizationSense() == 0)
			green = 1.0;
		else if(radiationPatternList.at(position)->GetPolarizationSense() == 1)
			red = 1.0;
		else
			blue = 1.0;
	}
}

void NECOutput::CalculateXYZ(const int i, double & x, double & y,
                            double & z, double & R)
{
	double gaindB = 0.0;

	/*
		We calculate the distance between the origin and the radiation point.
		We take to dB the relationship between the TotalGain and the maxPowerGain.
		Then we calculate a linear scale that makes correspond dBMinimum
		with (0,0,0) and TotalGain/maxPowerGain=1 to some point with
		radius=1
	*/

	gaindB = 10.0*log10(radiationPatternList.at(i)->GetTotalGain()/maxPowerGain);
	R = ((-1.0/dBMinimum)*gaindB)+1;

	if(dBMinimum < gaindB )
	{
		x = R*cos(radiationPatternList.at(i)->GetPhiAngle()*M_PI/180.0)*
		    sin(radiationPatternList.at(i)->GetThetaAngle()*M_PI/180.0);
		z = -1.0*R*sin(radiationPatternList.at(i)->GetPhiAngle()*M_PI/180.0)*
		    sin(radiationPatternList.at(i)->GetThetaAngle()*M_PI/180.0);
		y = R*cos(radiationPatternList.at(i)->GetThetaAngle()*M_PI/180.0);
	}
	// We don't have dBMinimum < gaindB
	else
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
		R = 0.0;
	}

}

void NECOutput::calculateSurface()
{
	/*
	We will read the matrix in rows, creating the necessary arrays.
	*/

	double red(0.0), green(0.0), blue(0.0);
	int position = 0;

	for(int row=0; row < vertexMatrix->getRows() - 1; row++)
	{
		for(int column=0; column < vertexMatrix->getColumns() - 1; column++)
		{
			surfaceVertexArray.append(vertexMatrix->getValue(row, column).x());
			surfaceVertexArray.append(vertexMatrix->getValue(row, column).y());
			surfaceVertexArray.append(vertexMatrix->getValue(row, column).z());

			position = row * vertexMatrix->getColumns() + column;
			calculateColors(position, vertexMatrix->getValue(row, column).w(),
			                red, green, blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);

			surfaceVertexArray.append(vertexMatrix->getValue(row + 1, column).x());
			surfaceVertexArray.append(vertexMatrix->getValue(row + 1, column).y());
			surfaceVertexArray.append(vertexMatrix->getValue(row + 1, column).z());

			position = (row + 1) * vertexMatrix->getColumns() + column;
			calculateColors(position, vertexMatrix->getValue(row + 1, column).w(),
			                red, green, blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);
		}
	}
}

void NECOutput::calculateMesh()
{
	/*
	We will read the matrix in rows, creating the necessary arrays.
	*/

	double red(0.0), green(0.0), blue(0.0);
	int position = 0;

	for(int row=0; row < vertexMatrix->getRows() - 1; row++)
	{
		for(int column=0; column < vertexMatrix->getColumns() - 1; column++)
		{
			meshVertexArray.append(vertexMatrix->getValue(row, column).x());
			meshVertexArray.append(vertexMatrix->getValue(row, column).y());
			meshVertexArray.append(vertexMatrix->getValue(row, column).z());

			position = row * vertexMatrix->getColumns() + column;
			calculateColors(position, vertexMatrix->getValue(row, column).w(),
			                red, green, blue);
			meshColorArray.append(red);
			meshColorArray.append(green);
			meshColorArray.append(blue);
			meshColorArray.append(alpha);

			meshVertexArray.append(vertexMatrix->getValue(row + 1, column).x());
			meshVertexArray.append(vertexMatrix->getValue(row + 1, column).y());
			meshVertexArray.append(vertexMatrix->getValue(row + 1, column).z());

			position = (row + 1) * vertexMatrix->getColumns() + column;
			calculateColors(position, vertexMatrix->getValue(row + 1, column).w(),
			                red, green, blue);
			meshColorArray.append(red);
			meshColorArray.append(green);
			meshColorArray.append(blue);
			meshColorArray.append(alpha);
		}
	}
}

void NECOutput::calculateInsideTriangles()
{
	int position = 0;
	double red(0.0), green(0.0), blue(0.0);

	for(int row=0; row < vertexMatrix->getRows(); row++)
	{
		for(int column=0; column < vertexMatrix->getColumns(); column++)
		{
			insideTrianglesVertexArray.append(vertexMatrix->getValue(row, column).x());
			insideTrianglesVertexArray.append(vertexMatrix->getValue(row, column).y());
			insideTrianglesVertexArray.append(vertexMatrix->getValue(row, column).z());

			position = row * vertexMatrix->getColumns() + column;
			calculateColors(position, vertexMatrix->getValue(row, column).w(),
			                red, green, blue);
			insideTrianglesColorArray.append(red);
			insideTrianglesColorArray.append(green);
			insideTrianglesColorArray.append(blue);
			insideTrianglesColorArray.append(alpha);

			insideTrianglesVertexArray.append(0.0);
			insideTrianglesVertexArray.append(0.0);
			insideTrianglesVertexArray.append(0.0);

			// We don't need to recalculate the color
			insideTrianglesColorArray.append(red);
			insideTrianglesColorArray.append(green);
			insideTrianglesColorArray.append(blue);
			insideTrianglesColorArray.append(alpha);
		}
	}

	// Now we repeat the process but reversing the order (reading per column)
	for(int column=0; column < vertexMatrix->getColumns(); column++)
	{
		for(int row=0; row < vertexMatrix->getRows(); row++)
		{
			insideTrianglesVertexArray.append(vertexMatrix->getValue(row, column).x());
			insideTrianglesVertexArray.append(vertexMatrix->getValue(row, column).y());
			insideTrianglesVertexArray.append(vertexMatrix->getValue(row, column).z());

			position = row * vertexMatrix->getColumns() + column;
			calculateColors(position, vertexMatrix->getValue(row, column).w(),
			                red, green, blue);
			insideTrianglesColorArray.append(red);
			insideTrianglesColorArray.append(green);
			insideTrianglesColorArray.append(blue);
			insideTrianglesColorArray.append(alpha);

			insideTrianglesVertexArray.append(0.0);
			insideTrianglesVertexArray.append(0.0);
			insideTrianglesVertexArray.append(0.0);

			// We don't need to recalculate the color
			insideTrianglesColorArray.append(red);
			insideTrianglesColorArray.append(green);
			insideTrianglesColorArray.append(blue);
			insideTrianglesColorArray.append(alpha);
		}
	}

}

void NECOutput::createMatrix()
{
	/*
	We have an array of vertices, and we want to create a matrix in which:
		* The rows are a set of vertices with the same phi angle value
		* The columns are a set of vertices with the same theta angle

	The first problem comes in that we do not know how many columns nor rows we
	need, so we first have to search the radiationPatternList for gathering this
	information (in this way, we can lately change the resolution of the surfaces
	without having to touch this structures).

	We know that both phi and theta start with a value of 0.0. We also know that
	the programs outputs all the set of theta values with a fixed phi, and then
	changes phi. So we must count how many phi and theta different values we
	have.
	*/

	// Columns hold the different sets of theta values
	int numberOfColumns = 0;
	// Rows hold the different sets of phi values
	int numberOfRows = 0;

	bool ready = false;

	while(!ready)
	{
		numberOfColumns++;
		if(radiationPatternList.at(numberOfColumns)->GetPhiAngle() != 0.0)
			ready = true;
	}

	numberOfRows = radiationPatternList.size() / numberOfColumns;

	// We know know the sizes, so we create the matrix
	vertexMatrix = new VertexMatrix(numberOfRows, numberOfColumns);

	/*
	Now we have to populate the matrix. We want the matrix to have the values in
	rectangular coordinates, so we must convert them.

	We will put R in the w coordinate.
	*/
	double x(0.0), y(0.0), z(0.0), R(0.0);

	for(int row=0; row < numberOfRows; row++)
	{
		for(int column=0; column < numberOfColumns; column++)
		{
			CalculateXYZ(row * numberOfColumns + column, x, y, z, R);
			vertexMatrix->setValue(row, column, Point4F(x, y, z, R));
		}
	}
}

void NECOutput::calculateTriangleNormal(double x1, double y1, double z1,
                                        double x2, double y2, double z2,
                                        double x3, double y3, double z3,
                                        double & x, double & y, double & z)
{
	x = (y2-y1)*(z3-z1)-(z2-z1)*(y3-y1);
	y = (z2-z1)*(x3-x1)-(x2-x1)*(z3-z1);
	z = (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
	double module = sqrt(x*x+y*y+z*z);
	x /= module;
	y /= module;
	z /= module;
}

