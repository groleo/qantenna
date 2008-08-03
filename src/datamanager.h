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
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "gl.h"
#include "neccontainer.h"

#include <QObject>
#include <QProcess>
#include <QtOpenGL>

class GLWidget;
class QDir;

/**
	This class takes cares of all the data in the program.
*/

class DataManager : public QObject
{
	Q_OBJECT

public:
	DataManager(GLWidget * gl, QObject * parent = 0);
	~DataManager();

	/// Returns the file name from the absolute path
	static QString cleanPathName(QString path);

	/// FIXME - Get the container list - Can this be avoided?
	QList<NECContainer*>* getContainerList();

	/// Frequency
	void setFrequency(int antennaIndex, double newFrequency);
	double getFrequency(int antennaIndex);

	/// Calculated
	void setCalculated(int antennaIndex, bool newVal);
	bool getCalculated(int antennaIndex);

	/// Show
	void setShow(int antennaIndex, bool newVal);
	bool getShow(int antennaIndex);

	/// In case we need to use more GLWidgets in the future...
	void setGLWidget(GLWidget * gl);

public slots:
	/// Hey you!!! Render!!!
	void Render();

	// Render selections
	void setRenderSurface(bool activate);
	void setRenderSpheres(bool activate);
	void setRenderMesh(bool activate);
	void setRenderInsideTriangles(bool activate);
	void setRenderGrid(bool activate);

	/// The minimum in the scale
	void setDBMinimum(double newDB);

	/// The radius of the spheres
	void setRadius(int newRadius);

	/// The transparency (alpha) of the surfaces
	void setAlpha(int newAlpha);

	/// Set surface size
	void setSurfaceSize(int newSurfaceSize);

	/// The radius of the antenna's components
	void setComponentsRadius(int newRadius);

	/// Calculate antenna at open
	void setCalcAtOpen(bool activate);

	/// Loading an antenna NEC file
	void openDialog();

	/// Remove selected antennas (selectedList should
	/// contain valid necContainerList indexes)
	void removeAntennas(QList<int> selectedList);

	/// Rebuild OpenGL lists of necContainerList
	void rebuildLists();

	/// Calculate the radiation pattern
	void calculateRadiationPattern();

signals:
	void updatedAntennaList();
	void antennasWithoutCalc(bool state);

	/// Some antenna finished the calculation of its pattern
	void finishedCalc();
	/// All antennas are calculated
	void finishedAllCalc();
	/// started to calc
	void startedCalc();

	// Log item
	void logStart(QString logo, QString msg);
	void log(QString msg);
	void logEndOK(bool ok);

private slots:
	/**
		If the last container was calculated,
		emits finishedCalc
	*/
	void checkFinishedCalc();

private:
	/// A list of NECInputs (antennas)
	QList<NECContainer*> necContainerList;

	/// File open dialog directory
	/**
	By default it will open in ".", but then we will save the last directory
	the user used.
	*/
	QDir currentDirectory;

	/// Opens and adds file fileName to necContainerList
	void openNECFile(QString fileName);

	/// FIXME WTF???
	bool fileExists(QString fileName);

	/// Should we calculate the antenna when opened?
	bool calcAtOpen;

	/// Grid enabled
	bool gridEnabled;

	/// A pointer to a GLWidget
	GLWidget *glWidget;

	/// FIXME Change after 0.2 release
	/// Needed to pass information in the Vis tab
	double dBMinumum;
	int radius;
	int alpha;
	int surfaceSize;
	int componentsRadius;
	bool surface, spheres, mesh, insideTriangles;
};

#endif //DATAMANAGER_H

