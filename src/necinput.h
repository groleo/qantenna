/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
 *   Gustavo González - gonzalgustavo en/at gmail.com                      *
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

#ifndef NECINPUT_H
#define NECINPUT_H

#include "gl.h"
#include "primitive.h"
#include "line.h"
#include "patch.h"
#include "cards/genericcard.h"

#include <QtOpenGL/QGLWidget>
#include <QList>

/**
	This class is very important because performs the NEC input file process that
	is saved in elementList. First ProcessData function transform information
	saved in elementList into a primitive format saved in primitiveList. This new
	format is compound by lines, patch and some cards (GM, GX, GA) that need
	a recursive processing. Then ProcessLine go over primitiveList and modify
	lines and patches according to GM, GX, etc. Finally primitiveList only
	contains lines and patches (sometimes could have some control cards that
	aren't used to draw the antenna) and is ready to be drawn by CreateOpenGLList.
*/
class NECInput : public QObject
{

	Q_OBJECT

public:
	NECInput(QString theFileName, QString theCreationTime, QWidget * parent = 0);
	~NECInput();

	/**
		This function appends a new element in the element list. It's used by
		NECInputParser
	*/
	void appendCard(GenericCard * theCard);

	///	Set a new maximum module.
	void SetMaxModule(double newMaxModule);

	/// Set the new simulation frequency
	void setSimulationFrequency(double newFrequency);

	///	Return the maximun module.
	double GetMaxModule();

	/// Return the wire (line) radius.
	double GetRadius();

	/**
		Returns the posistion of the center of the radiating element in the normal
		axis space (not the OGL's axes)
	*/
	void GetPosition(double & newX, double & newY, double & newZ);

	/// Returns the NEC file's frequency
	double getFrequency() const;

	/// The function ProcessData is the start of the information procedure.
	/// It converts data stored in elementList to a primitive format, more apropiate
	/// to process it. Then it call ProcessLine function.
	void ProcessData();

	/// Calls the list made by CreateOpenGLList.
	void Render();

	/// We must return the file name.
	QString GetFileName();

	/// Create input.necin
	void createNECInputFile();

public slots:
	/// Set the radius of the structure components.
	void SetRadius(double newRadius);

	/**
		Setfrequency sets new frequency parameters (or change them) and rewrite the
		NECInput file. If FR card doesn't exist, it inserts one after GE card with the
		new parameters. The frequency parameters are the following:
		Type indicates if increment is linear (0) or multiplicative (1)
		nSteps is the number of frequency steps.
		newFrequency is the simulation frequency
		stepInc the frequency step increment.
	*/
	void SetFrequency(int type, int nSteps, double newFrequency, double stepInc);

private:
	/**
		This function continues with the procedure of processing the data.
		It goes over the primitive list and execute GM, GX and GA functions.
	*/
	void ProcessPrimitive();

	/// Finally when all the structure geometry cards are processed, CreateOpenGLList
	/// draw the antenna.
	void CreateOpenGLList();

	/// Transformate normalizes the primitive's ends and change the axis to OGL
	/// format.
	void Transformate(QVector<double> & end);

	/// This private function is used by ProcessPrimitive to process GM card. It
	/// only make the code more pleasing to read.
	void ProcessGMCard(int index);

	/// This private function is used by ProcessPrimitive to process GX card. It
	/// only make the code more pleasing to read.
	void ProcessGXCard(int index);

	/// This private function is used by ProcessPrimitive to process GA card. It
	/// only make the code more pleasing to read.
	void ProcessGACard(int index);

	/** This private function is used by ProcessData to process SP card. It
	calculate the patch ends from data stored in elementList. The four patch
	shapes are:
	NS = 0, Arbitrary patch shape.
	NS = 1, Rectangular patch shape.
	NS = 2, Triangular patch shape.
	NS = 3, Quadrilateral patch shape.
	Note: NS is stored in element->parameter(1).
	*/
	void ProcessSPCard(int index);

	/// If module (function parameter) is larger than maxmodule, this function
	/// copy module into maxmodule.
	void CompareModule(double module);

	/// The filename we are processing
	QString fileName;

	/// We want to know when is the first time we find a FR card
	bool foundFRCard;

	/**
		The original frequency is the frequency established by the nec file.
		This value will not sync with NECContainer's if the last one is changed.
	*/
	double frequency;

	/// The lines vertex array
	QVector<double> linesVertexArray;
	/// The triangles vertex array
	QVector<double> trianglesVertexArray;
	/// The quads vertex array
	QVector<double> quadsVertexArray;

		/// The lines color array
	QVector<double> linesColorArray;
	/// The triangles color array
	QVector<double> trianglesColorArray;
	/// The quads color array
	QVector<double> quadsColorArray;

	/// It's the end's maximun module drawn. It's used to normalize the structure
	/// to 1.
	double maxModule;

	/// It indicates (tag number) the radiating element, if this exist.
	int radiatingElement;

	/**
		It's the center position of the antenna. It's used to move the radiation
		pattern.
	*/
	QVector<double> centerPosition;

	/// It's setted when a ground plane is present.
	bool groundPlane;

	/// It's the wire radius.
	double radius;

	/// The quadric for the tubes
	GLUquadricObj *quad;

	/// PrimitiveList store the data in a more apropiate format to process it.
	QList<Primitive*> primitiveList;

	/// List of cards
	QList<GenericCard*> cardsList;

	/**
		The creation time, to avoid overwritting of temp files between different
		process
	*/
	QString creationTime;
};
#endif //NECINPUT_H
