/***************************************************************************
 *   Copyright (C) 2007 by                                                 *
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

#ifndef GMCARD_H
#define GMCARD_H

#include "genericcard.h"
#include <QString>

/**
  Coordinate Transformation
  Translate or rotate a structure with respect to the coordinate system or to
  generate new structures translated or rotated from the original.
*/

class GMCard : public GenericCard
{
public:
  /**
   * \param theTagNumberIncrement Tag number increment.
   * \param theNumberOfNewStructures Number of new structures to be generated.
   * \param theXRotationAngle Angle in degrees through wich the structure is
   * rotated about the X-axis. A positive angle causes a right-hand rotation.
   * \param theYRotationAngle Angle of rotation about the Y-axis.
   * \param theZRotationAngle Angle of rotation about the Z-axis.
   * \param theXTranslation X component of vector by wich the structure is
   * translated with respect the coordinate system.
   * \param theYTranslation Y component of vector by wich the structure is
   * translated with respect the coordinate system.
   * \param theZTranslation Z component of vector by wich the structure is
   * translated with respect the coordinate system.
   * \param theInitialTag input in decimal but rounded to nearest integer before
   * use. Tag numbers are searched sequentially until a segment having a tag of
   * this segment ??? through the end of the sequence of segments is moved by
   * the card. If this field is blan (usual case) or zero. the entire structure is moved.
   */
  GMCard(int theTagNumberIncrement, int theNumberOfNewStructures,
         double theXRotationAngle, double theYRotationAngle,
         double theZRotationAngle, double theXTranslation,
         double theYTranslation, double theZTranslation,
         double theInitialTag);

  int getTagNumberIncrement() const;
  int getNumberOfNewStructures() const;
  double getXRotationAngle() const;
  double getYRotationAngle() const;
  double getZRotationAngle() const;
  double getXTranslation() const;
  double getYTranslation() const;
  double getZTranslation() const;
  double getInitialTag() const;

  QString getCard();

private:
  int tagNumberIncrement;
  int numberOfNewStructures;
  double xRotationAngle;
  double yRotationAngle;
  double zRotationAngle;
  double xTranslation;
  double yTranslation;
  double zTranslation;
  double initialTag;

};

#endif // GFCARD_H


