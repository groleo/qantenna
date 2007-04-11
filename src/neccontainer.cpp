/***************************************************************************
 *   Copyright (C) 2005-2006 by                                            *
 *   Lisandro Damián Nicanor Pérez Meyer - perezmeyer en/at gmail.com      *
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

#include "neccontainer.h"
#include "glwidget.h"
#include "necinputparser.h"
#include "datamanager.h" // uses static cleanPathName
#include "loadthread.h"
#include <QDir>

NECContainer::NECContainer(QString theFilename, GLWidget * gl,
                           QObject * parent) : QObject(parent)
{
	glWidget = gl;
	fileName = theFilename;

	/*
		We grab the system's time to create temp files that have a very little
		chance to overwrite themselves if multiple process are running in the
		same machine
	*/
	QTime time;
	time.start();
	creationTime = time.toString("hhmmsszzz");

	// Just in case something fails, we set the frequency to 128.0 MHz
	frequency = 128.0;

	// We create the necInput
	necInput = new NECInput(theFilename,creationTime);

	// We parse the input file
	NECInputParser(necInput);
	// And then we process it's data
	necInput->ProcessData();
	// We get the frequency
	frequency = necInput->getFrequency();

	radiationPatternCalculated = false;

	show = true;
}

NECContainer::~NECContainer()
{
	delete necInput;
	delete necOutput;

	// And finally we must remove all the temporary files
	QString thePath = QDir::tempPath();
	// Add an extra separator in case the above funtion does not returns it
	thePath.append("/");

	QFile file(thePath + "input" + creationTime +".necin");
	if(file.exists())
		file.remove();

	file.setFileName(thePath + "output" + creationTime + ".necout");
	if(file.exists())
		file.remove();
}

QString NECContainer::getFileName()
{
	return fileName;
}

double NECContainer::getFrequency()
{
	return frequency;
}

bool NECContainer::getShow()
{
	return show;
}

bool NECContainer::getRadiationPatternCalculated()
{
	return radiationPatternCalculated;
}

void NECContainer::Render()
{
	if(!show) return;

	necInput->Render();
	if(radiationPatternCalculated)
		necOutput->Render();
}

void NECContainer::setFrequency(double newFrequency)
{
	frequency = newFrequency;
	radiationPatternCalculated = false;
	// We set necInput to it's new frequency
	necInput->setSimulationFrequency(newFrequency);
	// We re-process the data
	necInput->ProcessData();
}

void NECContainer::setComponentsRadius(double newRadius)
{
	necInput->SetRadius(newRadius);
}

void NECContainer::setDisplacement()
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double temp;

	// We get the real coordinates of the center
	necInput->GetPosition(x,y,z);

	// We now transform between real and OGL coordinates
	temp = -1.0*y;
	y = z;
	z = temp;

	// And we pass it to the radiattion pattern
	necOutput->setDisplacement(x,y,z);
}

void NECContainer::setRenderSurface(bool render)
{
	necOutput->setRenderSurface(render);
}

void NECContainer::setRenderSpheres(bool render)
{
	necOutput->setRenderSpheres(render);
}

void NECContainer::setRenderMesh(bool render)
{
	necOutput->setRenderMesh(render);
}

void NECContainer::setRenderInsideTriangles(bool render)
{
	necOutput->setRenderInsideTriangles(render);
}

void NECContainer::setDBMinimum(double newDB)
{
	necOutput->setDBMinimum(newDB);
}

void NECContainer::setRadius(double newRadius)
{
	necOutput->setRadius(newRadius);
}

void NECContainer::setAlpha(double newAlpha)
{
	necOutput->setAlpha(newAlpha);
}

void NECContainer::setSurfaceSize(double surfaceSize)
{
	necOutput->setRo(surfaceSize);
}

void NECContainer::setShow(bool newShow)
{
	show= newShow;
}

void NECContainer::setRadiationPatternCalculated(bool newVal)
{
	radiationPatternCalculated= newVal;
}

void NECContainer::setColorScheme(int theColorScheme)
{
	necOutput->setColorScheme(theColorScheme);
}

void NECContainer::calculateRadiationPattern()
{
	LoadThread *necThread = new LoadThread(this);
	connect(necThread, SIGNAL(finished()),
			this, SLOT(renderFile()));
	necThread->start();
	//necThread->wait();
}

void NECContainer::rebuildLists()
{
	glWidget->makeCurrent();
	necInput->ProcessData();
	necOutput->ProcessData();
}

void NECContainer::renderFile()
{
	// This funcion is called when the thread that calls nec2++ ends
	emit logStart("spattern.png", tr("Rendering \"<font color=\"#000066\">")
		+ DataManager::cleanPathName(fileName) + "</font>\"... ");

	glWidget->makeCurrent();

	necOutput->ProcessData();

	// We render the results
	radiationPatternCalculated = true;
	Render();

	glWidget->update();

	emit logEndOK(true);

	emit finishedCalc();
}

void NECContainer::loadFile()
{
	// The path to the temporary directory
	QString thePath = QDir::tempPath();
	// Add an extra separator in case the above funtion does not returns it
	thePath.append("/");

	if(radiationPatternCalculated)
	{
		// We delete the previous necOutput
		delete necOutput;
		// And the associated file
		QFile file(thePath + "output" + creationTime +".necout");
		if(file.exists())
			file.remove();
	}

	// And we create a new one
	necOutput = new NECOutput(glWidget);

	// We generate input.necin
	necInput->createNECInputFile();

	// FIXME The antenna's frequency should be passed to the UI

	// FIXME Check that input.necin exists

	// Now we pass the displacement of the antenna to necOutput
	setDisplacement();

	// A QProcess to call nec2
	QProcess *theProcess = new QProcess;
	QString program = "nec2++";

	// The arguments
	QStringList arguments;
	arguments << "-i" << thePath + "input" + creationTime + ".necin";
	arguments << "-o" << thePath + "output" + creationTime + ".necout";

	// We start the process
	theProcess->start(program,arguments);
	// And we wait until it finishes
	theProcess->waitForFinished();

	// We open the radiation pattern
	NECOutputParser(necOutput,thePath + "output" + creationTime + ".necout");
}
