/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
 *   Lisandro Damián Nicanor Pérez Meyer - perezmeyer en/at gmail.com      *
 *   Gustavo González - gonzalgustavo en/at gmail.com                      *
 *   Pablo Odorico  pablo.odorico en/at gmail.com                          *
 *   Graham Seale graham.seale en/at gmail.com                             *
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

/**
  In this file you will see a lot of times a call to glWidget->makeCurrent().
  It happens that, in order to use OGL functions properly,
  GLWidget::makeCurrent() must be called beforehand.
  I tried to solve this with the signal/slot mechanism, but I couldn't get it
  to work except if I execute a glWidget->makeCurrent() at least one time
  before in this source code.
  The extrange thing is that the GLWidget::makeCurrent() seems to have a
  "one level" memory, so the instances of NECOutput doesn't seem to need
  the pointer to make the call.
  This note applies also to the NECContainer class
*/

#include <QtOpenGL>
#include <QDir>
#include <QTime>
#include <QList>
#include <QUrl>

#include "gl.h"
#include "datamanager.h"
#include "neccontainer.h"
#include "glwidget.h"
#include "loadthread.h"

DataManager::DataManager(GLWidget * gl, QObject * parent) : QObject(parent)
{
  gridEnabled = true;
  glWidget = gl;

  // calcAtOpen must start in sync with fileListCalculate (checkbox)
  calcAtOpen= true;

  // Current directory startup.
  currentDirectory = QDir::homePath();

  // Should start in sync with the GUI
  dBMinumum= -25;
  radius= 50;
  alpha= 50;
  surfaceSize= 10;
  componentsRadius= 2;
  surface= true;
  spheres= mesh= insideTriangles= false;
}

DataManager::~DataManager()
{
  glWidget->makeCurrent();

  // NOTICE do we need to do this?
  // We should empty the containers list
  foreach(NECContainer *container, necContainerList)
    delete container;
}

void DataManager::calculateRadiationPattern()
{
  int calcNumber= 0;

  emit startedCalc();

  foreach(NECContainer *container, necContainerList) {
    if(!container->getRadiationPatternCalculated()) {
      emit logStart("sexec.png", tr("Calculating")+" \"<font color=\"#000066\">"
        + DataManager::cleanPathName(container->getFileName()) + "</font>\"... ");

      container->calculateRadiationPattern();

      emit logEndOK(true);
      calcNumber++;
    }
  }

  // If no pattern is calculated, finishedAllCalc
  // must be called (given that checkFinishedCalc()
  // will never be called)
  if(!calcNumber) emit finishedAllCalc();

  emit updatedAntennaList();
  emit antennasWithoutCalc(false);
}

QString DataManager::cleanPathName(QString path)
{
  // We clean the path
  path = QDir::cleanPath(path);
  return path.split("/").last();
}

QList<NECContainer*>* DataManager::getContainerList()
{
  return &necContainerList;
}

double DataManager::getFrequency(int antennaIndex)
{
  return necContainerList.at(antennaIndex)->getFrequency();
}

void DataManager::setFrequency(int antennaIndex, double newFrequency)
{
  necContainerList.at(antennaIndex)->setFrequency(newFrequency);
}

bool DataManager::getCalculated(int antennaIndex)
{
  return necContainerList.at(antennaIndex)->getRadiationPatternCalculated();
}

void DataManager::setCalculated(int antennaIndex, bool newVal)
{
  necContainerList.at(antennaIndex)->setRadiationPatternCalculated(newVal);
  emit antennasWithoutCalc(!newVal);
}

bool DataManager::getShow(int antennaIndex)
{
  return necContainerList.at(antennaIndex)->getShow();
}

void DataManager::setShow(int antennaIndex, bool newVal)
{
  necContainerList.at(antennaIndex)->setShow(newVal);
}

void DataManager::setGLWidget(GLWidget * gl)
{
  glWidget = gl;
}

void DataManager::Render()
{
  glWidget->makeCurrent();
  if(gridEnabled) glWidget->renderGrid();
  foreach(NECContainer *container, necContainerList) {
    container->Render();
  }
}

void DataManager::setComponentsRadius(int newRadius)
{
  foreach(NECContainer *container, necContainerList)
    container->setComponentsRadius((double)newRadius);
  glWidget->update();
  componentsRadius= newRadius;
}

void DataManager::setRenderSurface( bool activate )
{
  glWidget->makeCurrent();
  foreach(NECContainer *container, necContainerList)
    container->setRenderSurface(activate);
  glWidget->update();
  surface= activate;
}

void DataManager::setRenderSpheres( bool activate )
{
  foreach(NECContainer *container, necContainerList)
    container->setRenderSpheres(activate);
  spheres= activate;
}

void DataManager::setRenderMesh( bool activate )
{
  foreach(NECContainer *container, necContainerList)
    container->setRenderMesh(activate);
  mesh= activate;
}

void DataManager::setRenderInsideTriangles( bool activate )
{
  foreach(NECContainer *container, necContainerList)
    container->setRenderInsideTriangles(activate);
  insideTriangles= activate;
}

void DataManager::setRenderGrid(bool activate)
{
  gridEnabled = activate;
}

void DataManager::setDBMinimum(double newDB)
{
  foreach(NECContainer *container, necContainerList)
    container->setDBMinimum(newDB);
  glWidget->update();
  dBMinumum= newDB;
}

void DataManager::setRadius(int newRadius)
{
  foreach(NECContainer *container, necContainerList)
    container->setRadius((double)newRadius/1000.0);
  glWidget->update();
  radius= newRadius;
}

void DataManager::setAlpha(int newAlpha)
{
  foreach(NECContainer *container, necContainerList)
    container->setAlpha((double)newAlpha/100.0);
  glWidget->update();
  alpha= newAlpha;
}

void DataManager::setSurfaceSize(int newSurfaceSize)
{
  foreach(NECContainer *container, necContainerList)
    container->setSurfaceSize((double)newSurfaceSize/10.0);
  glWidget->update();
  surfaceSize= newSurfaceSize;
}

void DataManager::removeAntennas(QList<int> selectedList)
{
  // The antennas need to be deleted starting with the
  // last (in necContainerList), otherwise after
  // deleting an element, the rest of the indexes in
  // "list" may (most likely) become invalid...

  // Sort list in reverse order
  qSort(selectedList.begin(), selectedList.end(), qGreater<int>());

  foreach(int index, selectedList) {
    emit logStart("sclose.png",tr("Closing")+" \"<font color=\"#000066\">"
    + cleanPathName(necContainerList.at(index)->getFileName()) + "</font>\"... ");

    necContainerList.removeAt(index);

    emit logEndOK(true);
  }

  // It may happen than a not-calculated antenna is deleted, so
  // we re-emit antennasWithoutCalc just in case
  bool needToCalc= false;
  for(int i=0; !needToCalc && i<necContainerList.count(); i++) {
    if(!necContainerList.at(i)->getRadiationPatternCalculated())
      needToCalc= true;
  }
  emit antennasWithoutCalc(needToCalc);

  emit updatedAntennaList();
}

// Drag and drop: new function to to the task of opening files so we can
// have both ways (drag+drop and File>Open) functional.
void DataManager::fileOpen(QStringList theFiles)
{
  QString fileName;

  while (!theFiles.isEmpty())
  {
    fileName = theFiles.first();
    theFiles.removeFirst();

    QApplication::restoreOverrideCursor();

    // TODO: Needs proper validation in addition to checking if the
    // file is already open.
    if(fileExists(fileName))
    {
      QMessageBox::information(NULL,"QAntenna",
      tr("The file \"")+cleanPathName(fileName)+tr("\" is already open."));
      }
      else
      {
        openNECFile(fileName);
      }
  }

  // Do the calculation after all the files are open by either route.
  if(calcAtOpen)
  {
    calculateRadiationPattern();
  }
  else
  {
    emit antennasWithoutCalc(true);
  }

  emit updatedAntennaList();
}

// Drag and drop: half of this function has been moved to fileOpen.
void DataManager::openDialog()
{
  // Removed fileNames; no longer needed
  QStringList filterList;
  QList<QUrl> sideBarUrls;
  QFileDialog dialog;

  // Just show the files we understand.
  filterList << tr("NEC files (*.nec)") << tr("All files (*.*)");
  dialog.setFilters(filterList);
  dialog.setDirectory(currentDirectory);
  // More than one file can be selected
  dialog.setFileMode(QFileDialog::ExistingFiles);

  // Give an URL to the examples
  sideBarUrls << QUrl::fromLocalFile(QString(EXAMPLES_PATH));
  dialog.setSidebarUrls(sideBarUrls);

  /*
    Seems that KDE's native dialog doesn't supports the side bar URL.
    Use Qt's one.
   */
  dialog.setOption(QFileDialog::DontUseNativeDialog);

  if(!dialog.exec()) return;

  // Keep the last directory
  currentDirectory = dialog.directory();

  fileOpen(dialog.selectedFiles());
}

void DataManager::openNECFile(QString fileName)
{
  // Should you call this function directly, make sure fileName
  // is valid (like QFileDialog does)

  emit logStart("sopen.png", tr("Opening")+" \"<font color=\"#000066\">" +
  cleanPathName(fileName) + "</font>\"... ");

  NECContainer *theContainer = new NECContainer(fileName, glWidget);

  necContainerList.append(theContainer);

  // Every NECContiner logs through this
  // class' logging functions
  connect(theContainer, SIGNAL(logStart(QString, QString)),
      this, SIGNAL(logStart(QString, QString)));
  connect(theContainer, SIGNAL(log(QString)),
      this, SIGNAL(log(QString)));
  connect(theContainer, SIGNAL(logEndOK(bool)),
      this, SIGNAL(logEndOK(bool)));

  connect(theContainer, SIGNAL(finishedCalc()),
      this, SIGNAL(finishedCalc()));
  // If this was the last container to be
  // calculated, finishedCalc will be emmited
  connect(theContainer, SIGNAL(finishedCalc()),
      this, SLOT(checkFinishedCalc()));

  emit logEndOK(true);

}

bool DataManager::fileExists(QString fileName)
{
  // Checks the filenames in the antenna list
  bool exists= false;
  for(int i=0; !exists && i<necContainerList.size(); ++i) {
    if(necContainerList.at(i)->getFileName() == fileName)
      exists= true;
  }
  return exists;
}

void DataManager::setCalcAtOpen(bool activate)
{
  calcAtOpen= activate;
}

void DataManager::rebuildLists()
{
  glWidget->makeGrid(0.0, 0.1, 2.0);
  foreach(NECContainer *container, necContainerList)
    container->rebuildLists();
}

void DataManager::checkFinishedCalc()
{
  // FIXME remove after .2
  // Sync with GUI
  foreach(NECContainer *container, necContainerList)	{
    if(container->getRadiationPatternCalculated()) {
      container->setRenderSurface(surface);
      container->setRenderSurface(surface);
      container->setRenderSpheres(spheres);
      container->setRenderMesh(mesh);
      container->setRenderInsideTriangles(insideTriangles);
      container->setDBMinimum(dBMinumum);
      container->setComponentsRadius((double)componentsRadius);
      container->setRadius((double)radius/1000.0);
      container->setAlpha((double)alpha/100.0);
      container->setSurfaceSize((double)surfaceSize/10.0);
    }
  }

  bool exit= false;
  int i= 0;
  while(!exit && i<necContainerList.size()) {
    if(!necContainerList.at(i)->getRadiationPatternCalculated())
      exit= true;
    i++;
  }
  if(!exit) emit finishedAllCalc();
}

