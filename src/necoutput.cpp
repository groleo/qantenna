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
#include <QtOpenGL/QGLWidget>
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

	listCompleted = false;
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
	glWidget->makeCurrent();
	if(!listCompleted)
	{
		// We inicialize the quadric
		quad = gluNewQuadric();
		gluQuadricNormals(quad, GLU_SMOOTH);

		// We create lists to make easier the plottings
		// The first phi position would always be zero
		phiStartList.append(0);
		// And also with the first value
		phiValues.append(0.0);

		for(int i=0; i<radiationPatternList.size(); i++)
			if(radiationPatternList.at(i)->GetPhiAngle()>phiValues.last())
			{
				phiStartList.append(i);
				phiValues.append(radiationPatternList.at(i)->GetPhiAngle());
			}
		listCompleted = true;
	}
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
	glEnableClientState(GL_NORMAL_ARRAY);

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
			glNormalPointer(GL_DOUBLE,0,surfaceNormalArray.data());
			// We draw the arrays
			glDrawArrays(GL_TRIANGLES,0, surfaceVertexArray.size()/3);
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
			glNormalPointer(GL_DOUBLE,0,meshNormalArray.data());
			glDrawArrays(GL_LINE_STRIP,0,meshVertexArray.size()/3);
		}
		if(insideTrianglesEnabled)
		{
			glVertexPointer(3,GL_DOUBLE,0,insideTrianglesVertexArray.data());
			glColorPointer(4,GL_DOUBLE,0,insideTrianglesColorArray.data());
			glNormalPointer(GL_DOUBLE,0,insideTrianglesNormalArray.data());
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
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double x1 = 0.0;
	double y1 = 0.0;
	double z1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	double z2 = 0.0;
	double normalX = 0.0;
	double normalY = 0.0;
	double normalZ = 0.0;
	double R0 = 0.0;
	double R1 = 0.0;
	double R2 = 0.0;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;


	for(int i=0; i<phiStartList.size()-1; i++)
		for(int j=0; j<(phiStartList.at(2)-phiStartList.at(1)-1); j++)
		{
			// First triangle
			CalculateXYZ(j+phiStartList.at(i),x,y,z,R0);
			CalculateXYZ(j+phiStartList.at(i+1),x2,y2,z2,R1);
			CalculateXYZ(j+1+phiStartList.at(i),x1,y1,z1,R2);

			// Vertex
			surfaceVertexArray.append(x);
			surfaceVertexArray.append(y);
			surfaceVertexArray.append(z);
			surfaceVertexArray.append(x2);
			surfaceVertexArray.append(y2);
			surfaceVertexArray.append(z2);
			surfaceVertexArray.append(x1);
			surfaceVertexArray.append(y1);
			surfaceVertexArray.append(z1);

			// Colors
			calculateColors(j+phiStartList.at(i),R0,red,green,blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);

			calculateColors(j+phiStartList.at(i+1),R1,red,green,blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);

			calculateColors(j+1+phiStartList.at(i),R2,red,green,blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);


			// Normals
			calculateTriangleNormal(x,y,z,x1,y1,z1,x2,y2,z2,normalX,normalY,normalZ);
			if( j > (phiStartList.at(2)-phiStartList.at(1)-1)/2)
			{
				normalX *= -1.0;
				normalY *= -1.0;
				normalZ *= -1.0;
			}
			surfaceNormalArray.append(normalX);
			surfaceNormalArray.append(normalY);
			surfaceNormalArray.append(normalZ);
			surfaceNormalArray.append(normalX);
			surfaceNormalArray.append(normalY);
			surfaceNormalArray.append(normalZ);
			surfaceNormalArray.append(normalX);
			surfaceNormalArray.append(normalY);
			surfaceNormalArray.append(normalZ);

			// Second triangle
			CalculateXYZ(j+phiStartList.at(i+1),x,y,z,R0);
			CalculateXYZ(j+1+phiStartList.at(i),x2,y2,z2,R1);
			CalculateXYZ(j+1+phiStartList.at(i+1),x1,y1,z1,R2);

			// Vertex
			surfaceVertexArray.append(x);
			surfaceVertexArray.append(y);
			surfaceVertexArray.append(z);
			surfaceVertexArray.append(x1);
			surfaceVertexArray.append(y1);
			surfaceVertexArray.append(z1);
			surfaceVertexArray.append(x2);
			surfaceVertexArray.append(y2);
			surfaceVertexArray.append(z2);

			// Colors
			calculateColors(j+phiStartList.at(i+1),R0,red,green,blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);

			calculateColors(j+1+phiStartList.at(i),R1,red,green,blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);

			calculateColors(j+1+phiStartList.at(i+1),R2,red,green,blue);
			surfaceColorArray.append(red);
			surfaceColorArray.append(green);
			surfaceColorArray.append(blue);
			surfaceColorArray.append(alpha);

			// Normals
			calculateTriangleNormal(x,y,z,x1,y1,z1,x2,y2,z2,normalX,normalY,normalZ);
			if( j < (phiStartList.at(2)-phiStartList.at(1)-1)/2)
			{
				normalX *= -1.0;
				normalY *= -1.0;
				normalZ *= -1.0;
			}
			surfaceNormalArray.append(normalX);
			surfaceNormalArray.append(normalY);
			surfaceNormalArray.append(normalZ);
			surfaceNormalArray.append(normalX);
			surfaceNormalArray.append(normalY);
			surfaceNormalArray.append(normalZ);
			surfaceNormalArray.append(normalX);
			surfaceNormalArray.append(normalY);
			surfaceNormalArray.append(normalZ);
		}
}

void NECOutput::calculateMesh()
{
	double x = 0;
	double y = 0;
	double z = 0;
	double R = 0;
	double red = 0;
	double green = 0;
	double blue = 0;

	for(int i=0; i<phiStartList.size()-1; i++)
	{
		for(int j=0; j<(phiStartList.at(2)-phiStartList.at(1)); j++)
		{
			// Vertex
			CalculateXYZ(j+phiStartList.at(i),x,y,z,R);
			meshVertexArray.append(x);
			meshVertexArray.append(y);
			meshVertexArray.append(z);

			// Colours
			calculateColors(j+phiStartList.at(i),R,red,green,blue);
			meshColorArray.append(red);
			meshColorArray.append(green);
			meshColorArray.append(blue);
			meshColorArray.append(alpha);

			// Normals does not need normalizing, they are already normalized
			meshNormalArray.append(x);
			meshNormalArray.append(y);
			meshNormalArray.append(z);

			// Vertex
			CalculateXYZ(j+phiStartList.at(i+1),x,y,z,R);
			meshVertexArray.append(x);
			meshVertexArray.append(y);
			meshVertexArray.append(z);

			// Colours
			calculateColors(j+phiStartList.at(i+1),R,red,green,blue);
			meshColorArray.append(red);
			meshColorArray.append(green);
			meshColorArray.append(blue);
			meshColorArray.append(alpha);

			// Normals does not need normalizing, they are already normalized
			meshNormalArray.append(x);
			meshNormalArray.append(y);
			meshNormalArray.append(z);
		}
	}
}

void NECOutput::calculateInsideTriangles()
{
	double x = 0;
	double y = 0;
	double z = 0;
	double R = 0;
	double red = 0;
	double green = 0;
	double blue = 0;

	for(int i=0; i<phiStartList.size()-1; i++)
		for(int j=0; j<(phiStartList.at(2)-phiStartList.at(1)); j++)
		{
			CalculateXYZ(j+phiStartList.at(i),x,y,z,R);
			calculateColors(j+phiStartList.at(i),R,red,green,blue);

			// Vertex
			insideTrianglesVertexArray.append(x);
			insideTrianglesVertexArray.append(y);
			insideTrianglesVertexArray.append(z);
			insideTrianglesVertexArray.append(0.0);
			insideTrianglesVertexArray.append(0.0);
			insideTrianglesVertexArray.append(0.0);

			// Colours
			insideTrianglesColorArray.append(red);
			insideTrianglesColorArray.append(green);
			insideTrianglesColorArray.append(blue);
			insideTrianglesColorArray.append(alpha);
			insideTrianglesColorArray.append(red);
			insideTrianglesColorArray.append(green);
			insideTrianglesColorArray.append(blue);
			insideTrianglesColorArray.append(alpha);

			/// FIXME calculate the normals accordingly
			insideTrianglesNormalArray.append(1.0);
			insideTrianglesNormalArray.append(0.0);
			insideTrianglesNormalArray.append(0.0);
			insideTrianglesNormalArray.append(1.0);
			insideTrianglesNormalArray.append(0.0);
			insideTrianglesNormalArray.append(0.0);
		}
	/*
		The other way. We check that there has been values added to the list,
		or we will have a segfault. Note that at least one value is incorpored
		in ProcessData(), so we must check if there at least are more than one.
	*/
	if(phiStartList.size() > 1)
	{
		for(int j=0; j<(phiStartList.at(2)-phiStartList.at(1)); j++)
			for(int i=0; i<phiStartList.size(); i++)
			{
				CalculateXYZ(j+phiStartList.at(i),x,y,z,R);
				calculateColors(j+phiStartList.at(i),R,red,green,blue);

				// Vertex
				insideTrianglesVertexArray.append(x);
				insideTrianglesVertexArray.append(y);
				insideTrianglesVertexArray.append(z);
				insideTrianglesVertexArray.append(0.0);
				insideTrianglesVertexArray.append(0.0);
				insideTrianglesVertexArray.append(0.0);

				// Colours
				insideTrianglesColorArray.append(red);
				insideTrianglesColorArray.append(green);
				insideTrianglesColorArray.append(blue);
				insideTrianglesColorArray.append(alpha);
				insideTrianglesColorArray.append(red);
				insideTrianglesColorArray.append(green);
				insideTrianglesColorArray.append(blue);
				insideTrianglesColorArray.append(alpha);

				/// FIXME calculate the normals accordingly
				insideTrianglesNormalArray.append(1.0);
				insideTrianglesNormalArray.append(0.0);
				insideTrianglesNormalArray.append(0.0);
				insideTrianglesNormalArray.append(1.0);
				insideTrianglesNormalArray.append(0.0);
				insideTrianglesNormalArray.append(0.0);
			}
	}
}

void NECOutput::calculateTriangleNormal(double x1, double y1, double z1,
                                        double x2, double y2, double z2,
                                        double x3, double y3, double z3,
                                        double & x, double & y, double & z)
{
	glWidget->makeCurrent();
	x = (y2-y1)*(z3-z1)-(z2-z1)*(y3-y1);
	y = (z2-z1)*(x3-x1)-(x2-x1)*(z3-z1);
	z = (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
	double module = sqrt(x*x+y*y+z*z);
	x /= module;
	y /= module;
	z /= module;
}

