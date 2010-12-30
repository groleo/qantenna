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

#ifndef NECCONTAINER_H
#define NECCONTAINER_H

#include "gl.h"
#include "necinput.h"
#include "necoutput.h"
#include "necoutputparser.h"

#include <QObject>
#include <QProcess>

/**
  This class takes cares of the NEC input and the NEC output.
  In this way, the data manager can have only one list of antennas with it's
  associated radiattion pattern, if existant.
*/

class GLWidget;

class NECContainer : public QObject
{
  Q_OBJECT

public:
  /**
    The constructor must receive the file name of the .nec and pointer to the
    GLWidget. See the note at the beggining of datamanager.cpp
  */
  NECContainer(QString theFilename, GLWidget * gl, QObject * parent = 0);
  ~NECContainer();

  /// Returns the name of the .nec file wich describes the antenna
  QString getFileName();

  /**
    Returns the starting frequency we will use to calculate the radiattion
    pattern.
  */
  double getFrequency();

  /// Rebuilds OpenGL lists for necInput and necOutput
  void rebuildLists();

  bool getShow();
  bool getRadiationPatternCalculated();

public slots:
  /// Would you please render your contents?
  void render();

  /// The frequency of the simulation
  void setFrequency(double newFrequency);

  /// The radius of the antenna's elements
  void setComponentsRadius(double newRadius);
  /// The displacement of the radiattion pattern
  void setDisplacement();

  // Render selections
  /// Sets if the radiattion pattern should be rendered as a surface
  void setRenderSurface(bool render);
  /// Sets if the radiation pattern should be rendered with spheres
  void setRenderSpheres(bool render);
  /// Sets if the radiation pattern should be rendered with a mesh
  void setRenderMesh(bool render);
  /**
    Sets if the radiation pattern should be rendered with triangles in it.
  */
  void setRenderInsideTriangles(bool render);

    /// The minimum in the scale
  void setDBMinimum(double newDB);
  /// The radius of the spheres
  void setRadius(double newRadius);
  /// The transparency (alpha) of the surfaces
  void setAlpha(double newAlpha);
  /// Set surface size
  void setSurfaceSize(double surfaceSize);

  /// Calculate the radiation pattern and parse the output
  void calculateRadiationPattern();

  void setShow(bool newShow);
  void setRadiationPatternCalculated(bool newVal);

  /**
    The color scheme defines how a RP point will be coloured.
    0: Use the gain
    1: Use the polarization sense
  */
  void setColorScheme(int theColorSchem);

  void loadFile();
  void renderFile();

signals:
  /// Log item
  void logStart(QString logo, QString msg);
  void log(QString msg);
  void logEndOK(bool ok);

  void finishedCalc();

private:

  /// A NECInput
  NECInput *necInput;
  /// A NECOutput
  NECOutput *necOutput;

  /// The file name
  QString fileName;

  /// The frequency
  double frequency;

  /// Did we calculate the radiattion pattern?
  bool radiationPatternCalculated;

  /// Should this antenna be rendered
  bool show;

  /**
    A pointer to the GLWidget. See the note at the beggining of datamanager.cpp
  */
  GLWidget * glWidget;

  /// The creation time to avoid overwriting of temp files between different process
  QString creationTime;
};

#endif //NECCONTAINER_H

