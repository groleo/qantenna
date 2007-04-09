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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datamanager.h"
#include "ui_mainwindowqantenna.h"
#include <QMainWindow>

// Forward declarations of classes, it makes the compiling much faster
class QSlider;
class GLWidget;
/**
	Class MainWindow is, obviously, the main window of the program.
	In it's constructor, it makes the connections neccesary for the program.
*/
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

public slots:

	/// fileList changes when a "View" checkBox or freq value does
	void fileListChanged(QTreeWidgetItem *item, int column);
	/// There was a change in fileList selection
	void fileListNewSelection();

	/// Things to do when the calculation process begins
	void startedCalc();
	/// Things to do when the calculation process ends
	void finishedCalc();
	/// This will be called when the are/aren't calculated antennas
	void antennasWithoutCalc(bool val);

	// Log functions
	/// logText contents changed, scroll to the bottom
	void logTextChanged();
	/// Start log with icon
	void logStart(QString logo, QString msg);
	/// Insert HTML to logText
	void log(QString str);
	/// Used to end a line with OK or ERROR
	void logEndOK(bool ok);
	/// Used for debugging
	void logDebug(QString func, QString msg);

	// About functions
	void about();
	void aboutQt();

	// Screenshot functions
	/// Asks for the desired resolution and renders the viewport
	/// into a QPixmap
	bool snapshot(QPixmap &pixmap);
	/// Saves image to file
	void renderToFile();
	/// Puts image into clipboard
	void renderToClipboard();

	// Antenna list functions
	/// Returns the list of indexes from DataManager::necContainerList
	/// of the selected antennas on the antenna list
	QList<int> selectedList();
	/// all the antennas on the antenna list
	QList<int> openedList();
	/// calculated antennas
	QList<int> calculatedList();

	/// Fill the antenna list with info from DataManager::necContainerList
	void syncFileList();

	/// Close selected antennas
	void close();
	/// Close all the opened antennas
	void closeAll();

signals:
	/// The signal we emmit to the data
	void setLinearScale(bool linear);

private:
	/**
		A reimplementation of a resize event so as to resize the widgets inside
		the MainWindow.
	*/
	/// Tha data manager
	DataManager *theData;

	/// The user interface
	Ui::MainWindowQAntenna ui;

	/// Information to keep user input when rendering to file/clipboard
	QString renderPath;
	int renderWidth, renderHeight;

	/// True when calculating
	bool calculating;

	/// Needed to prevent event loops
	bool disableFileListEvents;

	/// Constant indexes of the antenna list
	static const int listColName = 0;
	static const int listColFrequency = 1;
	static const int listColShow = 3;
	static const int listColCalc = 2;
	static const int listColPath = 4;
	static const int listColIndex = 5;

};

#endif
