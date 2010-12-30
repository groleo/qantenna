/***************************************************************************
 *   Copyright (C) by                                                      *
 *   2005 Gustavo González - gonzalgustavo en/at gmail.com                 *
 *   2005-2010 Lisandro Damián Nicanor Pérez Meyer -                       *
 *             perezmeyer en/at gmail.com                                  *
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

#include <QGLWidget>
#include <QList>

/**
  \class NECInput necinput.h
  \brief Stores and processes data related with the description of an antenna.

  - Processes the file containing an antenna description (called "NEC input"
    trough QAntenna) wich is then saved into elementList.
  - Creates the data to be sent to OpenGL for rendering.

  This class parses the NEC input file on creation populating cardsList. It then
  calls processData to populate the primitiveList. This new format is compounded
  by lines, patches and some cards (GM, GX, GA) that need recursive processing.

  Then processLine goes over primitiveList and modifies lines and patches
  according to GM, GX, etc.

  Finally primitiveList only contains lines and patches (sometimes could
  have some control cards that aren't used to draw the antenna) and is ready to
  be used by createOpenGLList.
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
  void setMaxModule(double newMaxModule);

  /// Set the new simulation frequency
  void setSimulationFrequency(double newFrequency);

  ///	Return the maximun module.
  double getMaxModule();

  /// Return the wire (line) radius.
  double getRadius();

  /**
    Returns the posistion of the center of the radiating element in the normal
    axis space (not the OGL's axes)
  */
  void getPosition(double & newX, double & newY, double & newZ);

  /// Returns the NEC file's frequency
  double getFrequency() const;

  /**
      \fn processData

      It converts data stored in elementList to primitives more apropiate to
      process. It then calls ProcessLine.
    */
  void processData();

  /// Calls the list made by CreateOpenGLList.
  void render();

  /// We must return the file name.
  QString getFileName();

  /// Create input.necin
  void createNECInputFile();

public slots:
  /// Set the radius of the structure components.
  void setRadius(double newRadius);

  /**
    Setfrequency sets new frequency parameters (or change them) and rewrite the
    NECInput file. If FR card doesn't exist, it inserts one after GE card with the
    new parameters. The frequency parameters are the following:
    Type indicates if increment is linear (0) or multiplicative (1)
    nSteps is the number of frequency steps.
    newFrequency is the simulation frequency
    stepInc the frequency step increment.
  */
  void setFrequency(int type, int nSteps, double newFrequency, double stepInc);

private:
  /**
    This function continues with the procedure of processing the data.
    It goes over the primitive list and execute GM, GX and GA functions.
  */
  void processPrimitive();

  /// Finally when all the structure geometry cards are processed, CreateOpenGLList
  /// draw the antenna.
  void createOpenGLList();

  /// Transformate normalizes the primitive's ends and change the axis to OGL
  /// format.
  void transformate(QVector<double> & end);

  /// This private function is used by ProcessPrimitive to process GM card. It
  /// only make the code more pleasing to read.
  void processGMCard(int index);

  /// This private function is used by ProcessPrimitive to process GX card. It
  /// only make the code more pleasing to read.
  void processGXCard(int index);

  /// This private function is used by ProcessPrimitive to process GA card. It
  /// only make the code more pleasing to read.
  void processGACard(int index);

  /**
    This private function is used by ProcessData to process SP card. It
    calculate the patch ends from data stored in elementList. The four patch
    shapes are:
      - NS = 0, Arbitrary patch shape.
      - NS = 1, Rectangular patch shape.
      - NS = 2, Triangular patch shape.
      - NS = 3, Quadrilateral patch shape.
    Note: NS is stored in element->parameter(1).
  */
  void processSPCard(int index);

  /// If module (function parameter) is larger than maxmodule, this function
  /// copy module into maxmodule.
  void compareModule(double module);

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
