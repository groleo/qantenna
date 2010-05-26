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

#include <QApplication>
#include <QMainWindow>
#include <QPixmap>
#include <QSplashScreen>
#include <QDebug>
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
	/* For every Qt graphical application, we need one QApplication instance */
	QApplication app(argc, argv);

	// Set the correct language
	// Translations for Qt
	QTranslator qtTranslator;

	//We get the system's locale
	QString locale = QLocale::system().name();

	qtTranslator.load("qt_" + locale, "/usr/share/qt4/translations",
	                  QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&qtTranslator);

	// Translations for QAntenna
	QTranslator myappTranslator;

#ifdef WIN32
	QString transdir=".";
#else
	QString transdir=PREFIX"/share/qantenna";
#endif

	myappTranslator.load("qantenna_" + locale, transdir);
	app.installTranslator(&myappTranslator);

	// The pixmap for the splash screen
	QPixmap pixmap(":/img/splash.png");

	// A splash screen
	QSplashScreen splashScreen(pixmap);
	splashScreen.show();

	// Check wheter we have OpenGL support or not
	splashScreen.showMessage(QObject::tr("Checking if there is OpenGL support in this machine"));
	if(!QGLFormat::hasOpenGL())
	{
		qDebug() << QWidget::tr("We don't have OpenGL support");
		QMessageBox::critical(0,"QAntenna - main.cpp",
		                      QWidget::tr("There is no OpenGL support in your system.<br>"
	                        "Closing QAntenna"));
		return 1;
	}

	// Load QAntenna
	splashScreen.showMessage(QObject::tr("Loading QAntenna"));

	// TODO Check that nec2++ is available
	/* And we need a main window, which must be showed */
	MainWindow mainWin;

	/* We show the window */
	mainWin.showMaximized();

	// And close the splash screen
	splashScreen.finish(&mainWin);

	/* The return value for the OS is returned by app */
	return app.exec();
}
