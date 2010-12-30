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

#include "necoutputparser.h"
#include "radiationpattern.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QLocale>
#include <QMessageBox>
#include <QtDebug>

// The ammount of data per line
#define DATALIST_NUMBER 12

int cleanRadiationPatternLine(QString line, QStringList & data)
{
  /**
    Returns:
    0: Linear sense
    1: Right sense
    2: Left sense
    3: No sense field
    -1: error
  */
  line = line.simplified();
  // TODO The following line should be enabled when CSV is enabled
  //line.remove(" ");


  data = line.split(" ");

  if( data.size() == DATALIST_NUMBER )
  {
    if(data.at(7).toUpper() == "LINEAR")
      return 0;
    else if(data.at(7).toUpper() == "RIGHT")
      return 1;
    else if(data.at(7).toUpper() == "LEFT")
      return 2;
    else
    {
      qDebug("NEC output parser - I have a sense that is neither LINEAR nor RIGHT nor LEFT\n");
      return -1;
    }
  }
  /*
    When data.at(4) (TotalGain) is -999.99 then we don't have the polarization
    sense. Then, we will check for data.size() == DATALIST_NUMBER-1.
  */
  else if( data.size() == (DATALIST_NUMBER-1))
  {
    //We have to tell the caller that we have one less field
    return 3;
  }
  else
  {
    qDebug("NEC output parser - The number of data and DATALIST_NUMBER doesn't match or there's another problem");
    qDebug() << "The line is " << line;
    qDebug() << "The data is " << data;
    return -1;
  }
}

int NECOutputParser(NECOutput * theNECOutput, QString theFileName)
{
  //NEC's outputs seem to be written with the C locale
  QLocale::setDefault(QLocale::C);
  QFile theFile(theFileName);

  //RadiationPattern * nullRP;
  //nullRP = new RadiationPattern(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0);

  //Let's check that the file exists
  if ( !theFile.exists() )
  {
    //The file does not exists
    qDebug("NEC output parser - The file does not exist\n");
    return 1;
  }
  //The file exists, but can we read it?
  if (!theFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    //We can not read the file
    qDebug("NEC output parser - I can not read the file\n");
    return 1;
  }

  //We generate the stream from the file
  QTextStream text(&theFile);
  //And we need some extra variables
  QString line;
  QStringList dataList;
  QString elDato;
  int sense = 0;

  //We opened the file, but is it empty?
  if(text.atEnd())
  {
    qDebug("The file is empty\n");
    return 1;
  }

  line = "";

  /*
    We search for the beggining of the radiation patterns
    The headers of the radiation patterns of nec2 and nec2++ differ
    in the seventh word, so I include both of them.
  */
  while((!text.atEnd()) &&
        (line != "DEGREES DEGREES DB DB DB RATIO DEG. VOLTS/M DEGREES VOLTS/M DEGREES") &&
        (line != "DEGREES DEGREES DB DB DB RATIO DEGREES VOLTS/M DEGREES VOLTS/M DEGREES")
      &&(!line.contains("GEOMETRY DATA CARD ERROR")) )
  {
    //We read a single line
    line = text.readLine();
    line = line.simplified();
  }

  if (line.contains("GEOMETRY DATA CARD ERROR"))
  {
    qDebug("Geometry data card error\n");
    return 1;
  }
  else if (text.atEnd())
  {
    qDebug("Radiation pattern data from nec2++ is missing\n");
    return 1;
  }
  else
  {

    RadiationPattern * newRP;

    //We scan the radiation patterns for data
    line = text.readLine();
    // We now check which kind of alignment we have
    sense = cleanRadiationPatternLine(line,dataList);

    // And now we check that we didn't have any errors
    if( sense == -1 )
      return 1;

    /*
      We scan the data until Theta <= 180, because all the rest of the data
      is redundant.
      For making the plotting of the surface much easier, we will need an
      extra set of data {(Theta == 180) == (Theta == 0) }. If we don't have
      Theta == 180, we will make one more iteration, which is considered
      below.
    */

    bool exists180 = false;

    while(!text.atEnd() && line !="" && dataList.at(1).toDouble()<=180.0)
    {
      if(sense != 3)
      {
        newRP = new RadiationPattern(dataList.at(0).toDouble(),
                    dataList.at(1).toDouble(),
                    dataList.at(2).toDouble(), dataList.at(3).toDouble(),
                    dataList.at(4).toDouble(), dataList.at(5).toDouble(),
                    dataList.at(6).toDouble(), sense,
                    dataList.at(8).toDouble(), dataList.at(9).toDouble(),
                    dataList.at(10).toDouble(), dataList.at(11).toDouble());
      }
      else
      {
        // We don't have a Sense field
        newRP = new RadiationPattern(dataList.at(0).toDouble(),
                    dataList.at(1).toDouble(),
                    dataList.at(2).toDouble(), dataList.at(3).toDouble(),
                    dataList.at(4).toDouble(), dataList.at(5).toDouble(),
                    dataList.at(6).toDouble(), sense,
                    dataList.at(7).toDouble(), dataList.at(8).toDouble(),
                    dataList.at(9).toDouble(), dataList.at(10).toDouble());
      }
      theNECOutput->setRadiationPattern(newRP);
      line = text.readLine();
      // We now check which kind of alignment we have
      if(line != "")
        sense = cleanRadiationPatternLine(line,dataList);
      // And now we check that we didn't have any errors
      if( sense == -1 )
        return 1;
      // Check if we have theta == 180
      if(dataList.at(1).toDouble() == 180.0)
        exists180 = true;
    }

    /*
      Now we must take into account the case in which we don't have
      Theta == 180 but a bigger number.
      Take into account that now Theta can't be less than 180.
    */
    double stop = 0.0;
    if(!exists180)
      stop = dataList.at(1).toDouble();
      while(!text.atEnd() && line !="" && dataList.at(1).toDouble()==stop)
      {
        if(sense != 3)
        {
          newRP = new RadiationPattern(dataList.at(0).toDouble(),
                      dataList.at(1).toDouble(),
                      dataList.at(2).toDouble(), dataList.at(3).toDouble(),
                      dataList.at(4).toDouble(), dataList.at(5).toDouble(),
                      dataList.at(6).toDouble(), sense,
                      dataList.at(8).toDouble(), dataList.at(9).toDouble(),
                      dataList.at(10).toDouble(), dataList.at(11).toDouble());
        }
        else
        {
          // We don't have a Sense field
          newRP = new RadiationPattern(dataList.at(0).toDouble(),
                      dataList.at(1).toDouble(),
                      dataList.at(2).toDouble(), dataList.at(3).toDouble(),
                      dataList.at(4).toDouble(), dataList.at(5).toDouble(),
                      dataList.at(6).toDouble(), sense,
                      dataList.at(7).toDouble(), dataList.at(8).toDouble(),
                      dataList.at(9).toDouble(), dataList.at(10).toDouble());
        }
        theNECOutput->setRadiationPattern(newRP);
        line = text.readLine();
        // We now check which kind of alignment we have
        if(line != "")
          sense = cleanRadiationPatternLine(line,dataList);
        // And now we check that we didn't have any errors
        if( sense == -1 )
          return 1;
    }

  }

  //All that has been opened must be closed before leaving
  theFile.close();
  return 0;
}// ParserNecOutput



