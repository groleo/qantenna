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
#ifndef NECOUTPUT_H
#define NECOUTPUT_H

#include "gl.h"
#include <QGLWidget>
#include <QList>
#include "radiationpattern.h"
#include "vertexmatrix.h"

class GLWidget;

/**
	This class holds the values that were returned from the execution of NEC
	and process them so as to make them rendereable by OpenGL.
*/

class NECOutput : public QObject
{

	Q_OBJECT

public:
	NECOutput(GLWidget * gl, QWidget * parent = 0);
	~NECOutput();

	/**
		Function to insert the radiation data that generates NECOutputParser
		into the list of radiation patterns.
	*/
	void SetRadiationPattern(RadiationPattern * newRadiationPattern);

	/// Change the color scheme
	void setColorScheme(int theColorScheme);

	/// Here we process the data in order to get OpenGL data
	void ProcessData();

	/// Will you please render?
	void Render();

	/**
		Sets the displacement of the radiattion pattern. Note that X, y and z
		are OGL's coordinates, not real coordinates.
	*/
	void setDisplacement(double & x, double & y, double & z);

	/// The minimum in the scale
	void setDBMinimum(double newDB);
	/// The radius of the spheres
	void setRadius(double newRadius);
	/// The transparency (alpha) of the surfaces
	void setAlpha(double newAlpha);

	/// Surface rendering
	void setRenderSurface(bool render);
	/// Spheres rendering
	void setRenderSpheres(bool render);
	/// Mesh rendering
	void setRenderMesh(bool render);
	/// Inside triangles rendering
	void setRenderInsideTriangles(bool render);

	/// A way to change the size of the surface
	void setRo(double newRo);

private:
	/// Color calcs
	void calculateColors(int position, const double R, double & red, double & green, double & blue);

	/// A private function to calculate the radiation pattern
	void CalculateXYZ(const int i, double & x, double & y,
	                  double & z, double & R);

	/// The triangles normals
	void calculateTriangleNormal(double x1, double y1, double z1,
	                             double x2, double y2, double z2,
	                             double x3, double y3, double z3,
	                             double & x, double & y, double & z);

	/// The surface calcs
	void calculateSurface();
	/// The inside triangles calcs
	void calculateInsideTriangles();

	/// Creates a matrix with the values of the vertex
	void createMatrix();

	/// List of radiation data obtained from parsing NEC's output
	QList<RadiationPattern*> radiationPatternList;

	/// Do we plot the surface?
	bool surfaceEnabled;
	/// Do we plot the spheres?
	bool spheresEnabled;
	///Do we plot the mesh?
	bool meshEnabled;
	/// Do we plot the inside triangles?
	bool insideTrianglesEnabled;

	/**
		The maximum power gain, so as to be able to normalize the
		radiation pattern
	*/
	double maxPowerGain;

	/// The quadric for the spheres
	GLUquadricObj *quad;

	/// The surface vertex array
	QVector<double> surfaceVertexArray;
	/// The inside triangles vertex array
	QVector<double> insideTrianglesVertexArray;

	/// The surface color array
	QVector<double> surfaceColorArray;
	/// The inside triangles color array
	QVector<double> insideTrianglesColorArray;

	/// The surface normal array
	QVector<double> surfaceNormalArray;
	/// The inside triangles normal array
	QVector<double> insideTrianglesNormalArray;

	/// The minimum value of Gain in dB whic corresponds to (0,0,0)
	double dBMinimum;
	/// The radius of the spheres
	double radius;
	/// Alpha of the colors
	double alpha;

	/// A matrix of vertices
	VertexMatrix * vertexMatrix;

	/// Size of the surfaces
	double ro;

	// Displacement of the surface
	/// Displacement in x
	double deltaX;
	/// Displacement in y
	double deltaY;
	/// Displacement in z
	double deltaZ;

	/// A pointer to a GLWidget
	GLWidget *glWidget;

	/**
		The color scheme defines how a RP point will be coloured.
		0: Use the gain
		1: Use the polarization sense
	*/
	int colorScheme;

};

#endif //NECOUTPUT_H

