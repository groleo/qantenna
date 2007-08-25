/***************************************************************************
 *   Copyright (C) 2005-7 by                                               *
 *   Lisandro Damián Nicanor Pérez Meyer - perezmeyer en/at gmail.com      *
 *   Gustavo González - gonzalgustavo en/at gmail.com                      *
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
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QLocale>
#include <QMessageBox>
#include <QtDebug>

#include "necinputparser.h"
#include "cards/allcards.h"


/**
	From version 0.2
	Please note: the original cards code has been developed using NEC's
	documentation available with Debian's nec2 package. At the moment of writing
	the parser, several doubts appeared, so I (Lisandro) decided to switch to a
	more appropiate source, Debian's nec2++ documentation (actually,
	users_guide.pdf included in the package). I confess the development should
	have started there, as we would use nec2++ as the backend for QAntenna.
*/

void parseTwoIntegers(QString & line, int & integer1, int & integer2,
                      double & double1, double & double2, double & double3,
                      double & double4, double & double5, double & double6,
                      double & double7)
{
	QLocale::setDefault(QLocale::C);
	QStringList stringList;
	line.replace(',',' ');
	line.simplified();
	stringList = line.split(' ');

	int i = 1;
	int integerNumber = 0;
	int doubleNumber = 0;

	while(i < stringList.size())
	{
		// We search for integers
		if(!stringList.at(i).contains('.') and integerNumber < 2
       and stringList.at(i) != "")
		{
			if(integerNumber == 0)
			{
				integer1 = stringList.at(i).toInt();
				integerNumber = 1;
			}
			else
			{
				integer2 = stringList.at(i).toInt();
				integerNumber = 2;
			}
		}
		else if(doubleNumber < 7 and stringList.at(i) != "")
		{
			// We have a double
			if(doubleNumber == 0)
			{
				double1 = stringList.at(i).toDouble();
				doubleNumber = 1;
			}
			else if(doubleNumber == 1)
			{
				double2 = stringList.at(i).toDouble();
				doubleNumber = 2;
			}
			else if(doubleNumber == 2)
			{
				double3 = stringList.at(i).toDouble();
				doubleNumber = 3;
			}
			else if(doubleNumber == 3)
			{
				double4 = stringList.at(i).toDouble();
				doubleNumber = 4;
			}
			else if(doubleNumber == 4)
			{
				double5 = stringList.at(i).toDouble();
				doubleNumber = 5;
			}
			else if(doubleNumber == 5)
			{
				double6 = stringList.at(i).toDouble();
				doubleNumber = 6;
			}
			else
			{
				double7 = stringList.at(i).toDouble();
				doubleNumber = 7;
			}
		}
		else if(stringList.at(i) != "")
		{
			qDebug() << "NECInputParser - parseTwoIntegers";
			qDebug() << QWidget::tr("The following line can not be parsed properly");
			qDebug() << line;
			qDebug() << QWidget::tr("The string list is");
			qDebug() << stringList;
			return;
		}
		i++;
	}
}

void parseFourIntegers(QString & line, int & integer1, int & integer2,
                       int & integer3, int & integer4, double & double1,
                       double & double2, double & double3, double & double4,
                       double & double5, double & double6)
{
	QLocale::setDefault(QLocale::C);
	QStringList stringList;
	line.replace(',',' ');
	line.simplified();
	stringList = line.split(' ');

	int i = 1;
	int integerNumber = 0;
	int doubleNumber = 0;
	while(i < stringList.size())
	{
		// We search for integers
		if(!stringList.at(i).contains('.') and integerNumber < 4
       and stringList.at(i) != "")
		{
			if(integerNumber == 0)
			{
				integer1 = stringList.at(i).toInt();
				integerNumber = 1;
			}
			else if(integerNumber == 1)
			{
				integer2 = stringList.at(i).toInt();
				integerNumber = 2;
			}
			else if(integerNumber == 2)
			{
				integer3 = stringList.at(i).toInt();
				integerNumber = 3;
			}
			else
			{
				integer4 = stringList.at(i).toInt();
				integerNumber = 4;
			}
		}
		else if(doubleNumber < 6 and stringList.at(i) != "")
		{
			// We have a double
			if(doubleNumber == 0)
			{
				double1 = stringList.at(i).toDouble();
				doubleNumber = 1;
			}
			else if(doubleNumber == 1)
			{
				double2 = stringList.at(i).toDouble();
				doubleNumber = 2;
			}
			else if(doubleNumber == 2)
			{
				double3 = stringList.at(i).toDouble();
				doubleNumber = 3;
			}
			else if(doubleNumber == 3)
			{
				double4 = stringList.at(i).toDouble();
				doubleNumber = 4;
			}
			else if(doubleNumber == 4)
			{
				double5 = stringList.at(i).toDouble();
				doubleNumber = 5;
			}
			else
			{
				double6 = stringList.at(i).toDouble();
				doubleNumber = 6;
			}
		}
		else if(stringList.at(i) != "")
		{
			qDebug() << "NECInputParser - parseFourIntegers";
			qDebug() << QWidget::tr("The following line can not be parsed properly");
			qDebug() << line;
			qDebug() << QWidget::tr("The string list is");
			qDebug() << stringList;
			return;
		}
		i++;
	}
}

int NECInputParser(NECInput * theNECInput)
{

	//NEC's outputs seem to be written with the C locale
	QLocale::setDefault(QLocale::C);
	QFile theFile(theNECInput->GetFileName());

	//Let's check that the file exists
	if ( !theFile.exists() )
	{
		//The file does not exists
		qDebug() << QWidget::tr("QAntenna - NEC input parser");
		qDebug() << QWidget::tr("The file does not exists");
		return 1;
	}
	//The file exists, but ¿can we read it?
	if (!theFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		//We can not read the file
		qDebug() << QWidget::tr("QAntenna - NEC input parser");
		qDebug() << QWidget::tr("I can not read the file");
		return 1;
	}
	//We generate the stream from the file
	QTextStream text(&theFile);

	//We opened the file, but ¿is it empty?
	if(text.atEnd())
	{
		qDebug() << QWidget::tr("QAntenna - NEC input parser");
		qDebug() << QWidget::tr("The file is empty");
		return 1;
	}

	// Some extra variables
	// The string that will hold each line of the card as we read it
	QString line;

	/*
		We read the file and fill NECInput's cardsList by calling
		NECInput::appendCard()
	*/

	// We need to create pointers to every type of card
	CECard * cecard = 0;
	CMCard * cmcard = 0;
	CPCard * cpcard = 0;
	EKCard * ekcard = 0;
	ENCard * encard = 0;
	EXCard * excard = 0;
	FRCard * frcard = 0;
	GACard * gacard = 0;
	GCCard * gccard = 0;
	GDCard * gdcard = 0;
	GECard * gecard = 0;
	GFCard * gfcard = 0;
	GHCard * ghcard = 0;
	GMCard * gmcard = 0;
	GNCard * gncard = 0;
	GRCard * grcard = 0;
	GSCard * gscard = 0;
	GWCard * gwcard = 0;
	GXCard * gxcard = 0;
	KHCard * khcard = 0;
	LDCard * ldcard = 0;
	NENHCards * nenhcards = 0;
	NTCard * ntcard = 0;
	NXCard * nxcard = 0;
	PQCard * pqcard = 0;
	PTCard * ptcard = 0;
	RPCard * rpcard = 0;
	SCCard * sccard = 0;
	SMCard * smcard = 0;
	SPCard * spcard = 0;
	TLCard * tlcard = 0;
	WGCard * wgcard = 0;
	XQCard * xqcard = 0;

	// We will also need some variables
	int integer1;
	int integer2;
	int integer3;
	int integer4;
	double double1;
	double double2;
	double double3;
	double double4;
	double double5;
	double double6;
	double double7;
	bool rpCardPresent = false;


	while(!text.atEnd())
	{
		integer1 = 0;
		integer2 = 0;
		integer3 = 0;
		integer4 = 0;
		double1 = 0.0;
		double2 = 0.0;
		double3 = 0.0;
		double4 = 0.0;
		double5 = 0.0;
		double6 = 0.0;
		double7 = 0.0;

		// We read a line
		line = text.readLine();
		// We put everything in uppercase
		line.toUpper();

		// Time to filter according the card type
		// CE card
		if(line.contains("CE"))
		{
			cecard = new CECard();
			theNECInput->appendCard(cecard);
			cecard = 0;
		}
		// CM card
		else if(line.contains("CM"))
		{
			line.remove("CM");
			cmcard = new CMCard(line);
			theNECInput->appendCard(cmcard);
			cmcard = 0;
		}
		// CP card
		else if(line.contains("CP"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			cpcard = new CPCard(integer1, integer2, integer3, integer4);
			theNECInput->appendCard(cpcard);
			cpcard = 0;
		}
		// EK card
		else if(line.contains("EK"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			ekcard = new EKCard(integer1);
			theNECInput->appendCard(ekcard);
			ekcard = 0;
		}
		else if(line.contains("EN"))
		{
			encard = new ENCard();
			theNECInput->appendCard(encard);
			encard = 0;
		}
		// EX card
		else if(line.contains("EX"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			excard = new EXCard(integer1,integer2,integer3,integer4,double1,double2,
			                    double3);
			theNECInput->appendCard(excard);
			excard = 0;
		}
		// EN card
		else if(line.contains("EN"))
		{
			encard = new ENCard();
			theNECInput->appendCard(encard);
			encard = 0;
		}
		// EX card
		else if(line.contains("EX"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			if(integer1 == 0 or integer1 == 5)
			{
				excard = new EXCard(integer1, integer2, integer3, integer4, double1,
				                    double2, double3);
			}
			else if(integer1 == 4)
			{
				excard = new EXCard(integer1, integer3, double1, double2, double3,
				                    double4, double5, double6);
			}
			else
			{
				excard = new EXCard(integer1, integer2, integer3, integer4, double1,
				                    double2, double3, double4, double5, double6);
			}
			theNECInput->appendCard(excard);
			excard = 0;
		}
		// FR card
		else if(line.contains("FR"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			frcard = new FRCard(integer1, integer2, double1, double2);
			theNECInput->appendCard(frcard);
			frcard = 0;
		}
		// GA card
		else if(line.contains("GA"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gacard = new GACard(integer1, integer2, double1, double2, double3,
			                    double4);
			theNECInput->appendCard(gacard);
			gacard = 0;
		}
		// GC card
		else if(line.contains("GC"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gccard = new GCCard(double1, double2, double3);
			theNECInput->appendCard(gccard);
			gccard = 0;
		}
		// GD card
		else if(line.contains("GD"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gdcard = new GDCard(double1, double2, double3, double4);
			theNECInput->appendCard(gdcard);
			gdcard = 0;
		}
		// GE card
		else if(line.contains("GE"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gecard = new GECard(integer1);
			theNECInput->appendCard(gecard);
			gecard = 0;
		}
		// GF card
		else if(line.contains("GF"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gfcard = new GFCard(integer1);
			theNECInput->appendCard(gfcard);
			gfcard = 0;
		}
		// GH card
		else if(line.contains("GH"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			ghcard = new GHCard(integer1, integer2, double1, double2, double3,
			                    double4, double5, double6, double7);
			theNECInput->appendCard(ghcard);
			ghcard = 0;
		}
		// GM card
		else if(line.contains("GM"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gmcard = new GMCard(integer1, integer2, double1, double2, double3,
			                    double4, double5, double6, double7);
			theNECInput->appendCard(gmcard);
			gmcard = 0;
		}
		// GN card
		else if(line.contains("GN"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			if(integer1 == -1)
				gncard = new GNCard();
			else
			{
				gncard = new GNCard(integer1, integer2, double1, double2, double3,
				                    double4, double5, double6);
			}
			theNECInput->appendCard(gncard);
			gncard = 0;
		}
		// GR card
		else if(line.contains("GR"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			grcard = new GRCard(integer1, integer2);
			theNECInput->appendCard(grcard);
			grcard = 0;
		}
		// GS card
		else if(line.contains("GS"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gscard = new GSCard(integer1,double1);
			theNECInput->appendCard(gscard);
			gscard = 0;
		}
		// GW card
		else if(line.contains("GW"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gwcard = new GWCard(integer1, integer2, double1, double2, double3,
			                    double4, double5, double6, double7);
			theNECInput->appendCard(gwcard);
			gwcard = 0;
		}
		// GX card
		else if(line.contains("GX"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			gxcard = new GXCard(integer1, integer2);
			theNECInput->appendCard(gxcard);
			gxcard = 0;
		}
		// KH card
		else if(line.contains("KH"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			khcard = new KHCard(double1);
			theNECInput->appendCard(khcard);
			khcard = 0;
		}
		// LD card
		else if(line.contains("LD"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			if(integer1 == -1)
				ldcard = new LDCard(integer1);
			else if(integer1 == 4)
			{
				ldcard = new LDCard(integer1, integer2, integer3, integer4, double1,
				                    double2);
			}
			else if(integer1 == 5)
			{
				ldcard = new LDCard(integer1, integer2, integer3, integer4, double1);
			}
			else
			{
				ldcard = new LDCard(integer1, integer2, integer3, integer4, double1,
				                    double2, double3);
			}
			theNECInput->appendCard(ldcard);
			ldcard = 0;
		}
		// NE card
		else if(line.contains("NE"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			nenhcards = new NENHCards(true, integer1, integer2, integer3, integer4,
			                          double1, double2, double3, double4, double5,
			                          double6);
			theNECInput->appendCard(nenhcards);
			nenhcards = 0;
		}
		// NH card
		else if(line.contains("NH"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			nenhcards = new NENHCards(false, integer1, integer2, integer3, integer4,
			                          double1, double2, double3, double4, double5,
			                          double6);
			theNECInput->appendCard(nenhcards);
			nenhcards = 0;
		}
		// NT card
		else if(line.contains("NT"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			if(integer2 == -1)
			{
				ntcard = new NTCard(integer1, integer2);
			}
			else
			{
				ntcard = new NTCard(integer1, integer2, integer3, integer4, double1,
				                    double2, double3, double4, double5, double6);
			}
			theNECInput->appendCard(ntcard);
			ntcard = 0;
		}
		// NX card
		else if(line.contains("NX"))
		{
			nxcard = new NXCard();
			theNECInput->appendCard(nxcard);
			nxcard = 0;
		}
		// PQ card
		else if(line.contains("PQ"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			pqcard = new PQCard(integer1, integer2, integer3, integer4);
			theNECInput->appendCard(pqcard);
			pqcard = 0;
		}
		// PT card
		else if(line.contains("PT"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			ptcard = new PTCard(integer1, integer2, integer3, integer4);
			theNECInput->appendCard(ptcard);
			ptcard = 0;
		}
		// RP card
		/// QAntenna needs only one RP card
		else if(line.contains("RP") and !rpCardPresent)
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);

			/// We will fix some values for our convenience
			float step= 2.4; // (before set check the following line)
			rpcard = new RPCard(integer1, (int)(360/step)+2, (int)(180/step)+2, integer4, 0.0,
			                    0.0, step, step, double5, double6);
			theNECInput->appendCard(rpcard);
			rpcard = 0;
			rpCardPresent = true;
		}
		// SC card
		else if(line.contains("SC"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			sccard = new SCCard(integer1, double1, double2, double3, double4, double5,
			                    double6);
			theNECInput->appendCard(sccard);
			sccard = 0;
		}
		// SM card
		else if(line.contains("SM"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			smcard = new SMCard(integer1, integer2, double1, double2, double3,
			                    double4, double5, double6);
			theNECInput->appendCard(smcard);
			smcard = 0;
		}
		// SP card
		else if(line.contains("SP"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			spcard = new SPCard(integer1, double1, double2, double3,
			                    double4, double5, double6);
			theNECInput->appendCard(spcard);
			spcard = 0;
		}
		// TL card
		else if(line.contains("TL"))
		{
			parseFourIntegers(line, integer1, integer2, integer3, integer4, double1,
			                  double2, double3, double4, double5, double6);
			if(integer2 == -1)
			{
				tlcard = new TLCard(integer1, integer2);
			}
			else
			{
				tlcard = new TLCard(integer1, integer2, integer3, integer4, double1,
				                    double2, double3, double4, double5, double6);
			}
			theNECInput->appendCard(tlcard);
			tlcard = 0;
		}
		// WG card
		else if(line.contains("WG"))
		{
			wgcard = new WGCard();
			theNECInput->appendCard(wgcard);
			wgcard = 0;
		}
		// XQ card
		else if(line.contains("XQ"))
		{
			parseTwoIntegers(line, integer1, integer2, double1, double2, double3,
			                 double4, double5, double6, double7);
			xqcard = new XQCard(integer1);
			theNECInput->appendCard(xqcard);
			xqcard = 0;
		}
	}

	//All that has been opened must be closed before leaving
	theFile.close();
	return 0;
}
