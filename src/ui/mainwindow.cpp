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

#include <QtGui>
#include <QtOpenGL/QtOpenGL>
#include <QProcess>
#include "glwidget.h"
#include "mainwindow.h"
#include "antennadelegate.h"
#include "ui/about.h"

// Just for Camera::limit
#include "camera.h"

#define Debug(str) logDebug(__func__, str)

MainWindow::MainWindow()
{

	ui.setupUi(this);

	// Instanciation of the data and the nec process
	theData = new DataManager(ui.widgetGL, this);

	// A status bar
	QStatusBar * statusBar = new QStatusBar(this);
	connect(ui.widgetGL,SIGNAL(setStatus(QString, int)),statusBar,
	        SLOT(showMessage(const QString & ,int)));
	setStatusBar(statusBar);

	// The magic of sinals/slots for rendering
	connect(ui.widgetGL,SIGNAL(RenderSurface()),
	        theData,SLOT(Render()));
	connect(ui.widgetGL,SIGNAL(rebuildLists()),
	        theData,SLOT(rebuildLists()));

	// Alpha connection
	connect(ui.horizontalSliderAlpha,SIGNAL(sliderMoved(int)),
	        theData,SLOT(setAlpha(int)));

	// Radius connection
	connect(ui.horizontalSliderRadius,SIGNAL(sliderMoved(int)),
	        theData,SLOT(setRadius(int)));

	// Scale connection
	connect(ui.horizontalSliderSurfaceScale,SIGNAL(sliderMoved(int)),
	        theData,SLOT(setSurfaceSize(int)));

	// Components radius connection
	connect(ui.horizontalSliderSegmentRadius,SIGNAL(sliderMoved(int)),
	        theData,SLOT(setComponentsRadius(int)));

	// Minimum dB connection
	connect(ui.doubleSpinBoxDBMinimum,SIGNAL(valueChanged(double)),
	        theData,SLOT(setDBMinimum(double)));

	// More signals/slots magic for the grid
	connect(ui.checkBoxGrid,SIGNAL(toggled(bool)),
	        theData,SLOT(setRenderGrid(bool)));
	connect(ui.checkBoxGrid,SIGNAL(toggled(bool)),
	        ui.widgetGL,SLOT(update()));
	// The grid
	ui.checkBoxGrid->setCheckState(Qt::Checked);

	// The rendering modes
	ui.checkBoxSurface->setCheckState(Qt::Checked);
	ui.checkBoxSpheres->setCheckState(Qt::Unchecked);
	ui.checkBoxMesh->setCheckState(Qt::Unchecked);
	ui.checkBoxInsideTriangles->setCheckState(Qt::Unchecked);

	// The signals and slots magic for the rendering modes
	connect(ui.checkBoxSurface,SIGNAL(toggled(bool)),
	        theData,SLOT(setRenderSurface(bool)));
	connect(ui.checkBoxSurface,SIGNAL(toggled(bool)),
	        ui.widgetGL,SLOT(update()));

	connect(ui.checkBoxSpheres,SIGNAL(toggled(bool)),
	        theData,SLOT(setRenderSpheres(bool)));
	connect(ui.checkBoxSpheres,SIGNAL(toggled(bool)),
	        ui.widgetGL,SLOT(update()));
	// Only enable the radius slider when showing spheres
	ui.horizontalSliderRadius->setEnabled(false);
	ui.labelSphereRadius->setEnabled(false);
	connect(ui.checkBoxSpheres,SIGNAL(toggled(bool)),
	        ui.horizontalSliderRadius,SLOT(setEnabled(bool)));
	connect(ui.checkBoxSpheres,SIGNAL(toggled(bool)),
	        ui.labelSphereRadius,SLOT(setEnabled(bool)));

	connect(ui.checkBoxMesh,SIGNAL(toggled(bool)),
	        theData,SLOT(setRenderMesh(bool)));
	connect(ui.checkBoxMesh,SIGNAL(toggled(bool)),
	        ui.widgetGL,SLOT(update()));

	connect(ui.checkBoxInsideTriangles,SIGNAL(toggled(bool)),
	        theData,SLOT(setRenderInsideTriangles(bool)));
	connect(ui.checkBoxInsideTriangles,SIGNAL(toggled(bool)),
	        ui.widgetGL,SLOT(update()));

	/*
	  QActions
	*/

	// Quit
	connect(ui.actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

	// Open
	connect(ui.actionOpen, SIGNAL(triggered()), theData, SLOT(openDialog()));
	// Close[all]
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionCloseAll, SIGNAL(triggered()), this, SLOT(closeAll()));

	// Calculate pattern
	connect(theData, SIGNAL(antennasWithoutCalc(bool)),
	        this, SLOT(antennasWithoutCalc(bool)));

	// About
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui.actionAboutQt, SIGNAL(triggered()), this, SLOT(aboutQt()));

	// Render
	connect(ui.actionRender, SIGNAL(triggered()), this, SLOT(renderToFile()));
	connect(ui.actionRenderClipboard, SIGNAL(triggered()), this, SLOT(renderToClipboard()));

	// Assign actions to QToolButtons
	ui.fileListOpen->setDefaultAction(ui.actionOpen);
	ui.fileListClose->setDefaultAction(ui.actionClose);
	ui.fileListCloseAll->setDefaultAction(ui.actionCloseAll);
	ui.fileListCalc->setDefaultAction(ui.actionCalc);

	/*
	  Antennas tab
	*/

	/// "Calculate at open" CheckBox
	connect(ui.fileListCalculate, SIGNAL(toggled(bool)),
			theData, SLOT(setCalcAtOpen(bool)));

	/// Log text with welcome msg
	ui.logText->insertHtml("<table width=\"100%\"><tr><td><img src=\":/icons/img/icon.png\"> \
	</td><td valign=middle>"+tr("Welcome to")+" <b>QAntenna</b>!</td></tr></table>");
	connect(ui.logText, SIGNAL(textChanged()),
			this, SLOT(logTextChanged()));
	// Clear log
	connect(ui.logTextClean, SIGNAL(clicked()),
			ui.logText, SLOT(clear()));
	// Classes that use the logger
	connect(theData, SIGNAL(logStart(QString, QString)),
			this, SLOT(logStart(QString, QString)));
	connect(theData, SIGNAL(log(QString)),
			this, SLOT(log(QString)));
	connect(theData, SIGNAL(logEndOK(bool)),
			this, SLOT(logEndOK(bool)));

	/// FileList
	// Sync with datamanager
	syncFileList();
	ui.tabParameters->setDisabled(true);
	connect(theData, SIGNAL(updatedAntennaList()),
			this, SLOT(syncFileList()));
	// Freq change
	connect(ui.fileList, SIGNAL(itemChanged(QTreeWidgetItem*, int)),
			this, SLOT(fileListChanged(QTreeWidgetItem*, int)));
	// Selection change
	connect(ui.fileList, SIGNAL(itemSelectionChanged()),
			this, SLOT(fileListNewSelection()));

	// Asign the item delegate
	ui.fileList->setItemDelegate(new AntennaDelegate(listColFrequency, listColIndex));

	// Table options
	ui.fileList->header()->setDefaultAlignment(Qt::AlignLeft);
	ui.fileList->header()->setMovable(false);
	ui.fileList->header()->setStretchLastSection(false);

	ui.fileList->header()->setResizeMode(listColName, QHeaderView::Stretch);
	ui.fileList->header()->setResizeMode(listColFrequency, QHeaderView::Stretch);
	ui.fileList->header()->setResizeMode(listColShow, QHeaderView::ResizeToContents);
	ui.fileList->header()->setResizeMode(listColCalc, QHeaderView::ResizeToContents);

	// The listColPath column contains the full path (used as id)
	ui.fileList->header()->hideSection(listColPath);
	// The listColIndex column contains the DataManager's antenna index
	ui.fileList->header()->hideSection(listColIndex);

	/// Start/End calculating events
	// _Every_ finishedCalc signal means that the file list has to
	// be updated ("gear" field)
	connect(theData, SIGNAL(finishedCalc()), this, SLOT(syncFileList()));
	// Things to do before and after calculating _all_ the patterns
	connect(theData, SIGNAL(finishedAllCalc()),	this, SLOT(finishedCalc()));
	connect(theData, SIGNAL(startedCalc()), this, SLOT(startedCalc()));

	connect(ui.actionCalc, SIGNAL(triggered()),	theData, SLOT(calculateRadiationPattern()));

	/*
	  Other
	*/

	// render to file/clipboard information
	renderPath= ".";
	renderWidth= 800;
	renderHeight= 600;

	calculating= false;
	disableFileListEvents= false;

	// This should make widgetGL as big as possible
	QList<int> list;
	list << height() << 1;
	ui.splitter_2->setSizes(list);
}

MainWindow::~MainWindow()
{
	delete theData;
}

void MainWindow::startedCalc()
{
	// The following widgets/actions should be disabled while calculating
	calculating= true;

	ui.actionOpen->setDisabled(true);
	ui.actionClose->setDisabled(true);
	ui.actionCloseAll->setDisabled(true);
	ui.actionRender->setDisabled(true);
	ui.actionRenderClipboard->setDisabled(true);
	ui.actionQuit->setDisabled(true);

	ui.fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tabParameters->setDisabled(true);

	// Clock cursor
	QApplication::setOverrideCursor(Qt::WaitCursor);
	// Status
	statusBar()->showMessage(tr("Calculating..."));
}

void MainWindow::finishedCalc()
{
	// Restore widgets/actions after calc
	calculating= false;

	ui.actionOpen->setEnabled(true);
	ui.actionClose->setEnabled(true);
	ui.actionCloseAll->setEnabled(true);
	ui.actionRender->setEnabled(true);
	ui.actionRenderClipboard->setEnabled(true);
	ui.actionQuit->setEnabled(true);

	ui.fileList->setEditTriggers(QAbstractItemView::AllEditTriggers);
	if(selectedList().count())
		ui.tabParameters->setEnabled(true);

	// Normal cursor
	QApplication::restoreOverrideCursor();
	// Status
	statusBar()->showMessage(tr("Done"), 3000);
}

void MainWindow::antennasWithoutCalc(bool val)
{
	ui.actionCalc->setEnabled(val);
	if(val) {
		statusBar()->showMessage(tr("Some antennas need to be calculated"), 6000);
	}
}

//
// fileList
//
void MainWindow::syncFileList()
{
	disableFileListEvents= true;

	// Pointer to necContainerList to obtain antenna info
	QList<NECContainer*> *necList = theData->getContainerList();

	// Full path of the selected elements
	QList<QString> selectedItemsText;

	foreach(QTreeWidgetItem *item, ui.fileList->selectedItems()) {
		selectedItemsText.append(item->text(listColPath));
	}

	ui.fileList->clear();

	NECContainer *container;
	QTreeWidgetItem* item = NULL;

	for(int i=0; i<necList->size(); i++) {
		container= necList->at(i);
		// New row
		item = new QTreeWidgetItem(ui.fileList);

		if(selectedItemsText.contains(container->getFileName())) {
			// this row was selected, should stay that way
			ui.fileList->setCurrentItem(item);
		}

		item->setText(listColName, DataManager::cleanPathName(container->getFileName()));
		item->setText(listColFrequency, QString("%1").arg(container->getFrequency(),0,'f',2));

		item->setText(listColCalc, (container->getRadiationPatternCalculated())?tr("Yes"):tr("No"));
		item->setTextAlignment(listColCalc, Qt::AlignCenter | Qt::AlignVCenter);

		item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		if(container->getShow())
			item->setCheckState(listColShow, Qt::Checked);
		else
			item->setCheckState(listColShow, Qt::Unchecked);
		item->setTextAlignment(listColShow, Qt::AlignCenter | Qt::AlignVCenter);

		// Hidden full path
		item->setText(listColPath, container->getFileName());
		// Hidden index
		item->setText(listColIndex, QString::number(i));
	}
/*
	// If we didn't select any item from the new necList
	// (the previously selected item no longer exists)
	// and there are items in the necList, we select the last one
	if(necList->size() && !ui.fileList->selectedItems().count()) {
		ui.fileList->setCurrentItem(item);
	}
*/
	// widgetGL may be out of sync, this happens at least when closing
	ui.widgetGL->update();

	disableFileListEvents= false;
}

void MainWindow::fileListChanged(QTreeWidgetItem *item, int column)
{
	// !calculating cos this event is called
	// while loading new antennas, and the show and freq fields of the
	// first antenna are incorrectly modified
	if(calculating) return;
	if(disableFileListEvents) return;

	int antennaIndex = item->data(listColIndex, Qt::DisplayRole).toInt();

	if(column == listColFrequency)
	{
		double newFreq= item->data(listColFrequency,Qt::DisplayRole).toDouble();

		// We check if the frequency has changed
		if(newFreq != theData->getFrequency(antennaIndex))
		{
 			// We change the antenna's frequency
			theData->setFrequency(antennaIndex, newFreq);
			theData->setCalculated(antennaIndex, false);

			syncFileList();
		}
	}

	// "View" checkbox
	if(column == listColShow) {
		bool newShow= item->checkState(listColShow)==Qt::Checked;
		if(newShow != theData->getShow(antennaIndex)) {
			theData->setShow(antennaIndex, newShow);
			ui.widgetGL->update();
		}
	}

	if(!openedList().count()) {
		// When all the antennas are gone
		// fileListNewSelection() is not called
		ui.tabParameters->setDisabled(true);
	}
}

void MainWindow::fileListNewSelection()
{
	if(calculating) return;
	if(disableFileListEvents) return;

	if(!openedList().count()) {
		// There aren't any items in fileList
		ui.actionCloseAll->setDisabled(true);
		ui.tabParameters->setDisabled(true);
	} else {
		// There are items in fileList
		ui.actionCloseAll->setEnabled(true);

		if(!selectedList().count()) {
			// No item is selected
			ui.actionClose->setDisabled(true);
			ui.tabParameters->setDisabled(true);
		} else {
			// There are selected items
			if(calculatedList().count())
				ui.tabParameters->setEnabled(true);
			ui.actionClose->setEnabled(true);
		}
	}
}

//
// Antenna list functions
//
QList<int> MainWindow::openedList()
{
	QList<int> indexList;
	foreach(QTreeWidgetItem *item, ui.fileList->findItems("*", Qt::MatchWildcard, listColIndex)) {
		indexList.append(item->text(listColIndex).toInt());
	}
	return indexList;
}

QList<int> MainWindow::selectedList()
{
	QList<int> indexList;
	foreach(QTreeWidgetItem *item, ui.fileList->selectedItems()) {
		indexList.append(item->text(listColIndex).toInt());
	}
	return indexList;
}

QList<int> MainWindow::calculatedList()
{
	QList<int> indexList;
	foreach(QTreeWidgetItem *item, ui.fileList->selectedItems()) {
		if(item->text(listColCalc)==tr("Yes")) {
			indexList.append(item->text(listColIndex).toInt());
		}
	}
	return indexList;
}

void MainWindow::close()
{
	theData->removeAntennas(selectedList());
}

void MainWindow::closeAll()
{
	theData->removeAntennas(openedList());
}

//
// logText
//
void MainWindow::logTextChanged()
{
	// Scroll to the bottom
	ui.logText->moveCursor(QTextCursor::End);
}

void MainWindow::logStart(QString logo, QString msg)
{
	// starts log line with "logo > "
	ui.logText->insertHtml("<br>");
	if(logo!="") {
		ui.logText->insertHtml("<img src=\":/icons/img/"+logo+"\" valign=bottom>&nbsp;" + msg);
	} else {
		ui.logText->insertHtml("<font color=\"#666666\"><b>&gt;</b></font> " + msg);
	}
}

void MainWindow::logDebug(QString func, QString msg)
{
	ui.logText->insertHtml("<br>");
	ui.logText->insertHtml("<img src=\":/icons/img/sbug.png\" valign=bottom\
	>&nbsp;<font color=\"#006666\">" + func + "()</font>: " + msg);
}
void MainWindow::log(QString str)
{
	// adds str to the current line
	ui.logText->insertHtml(str);
}

void MainWindow::logEndOK(bool ok)
{
	if(ok)
		ui.logText->insertHtml("<font color=\"#006600\"><b>"+tr("OK")+"</b></font>");
	else
		ui.logText->insertHtml("<font color=\"#660000\"><b>"+tr("Error")+"</b></font>");
}

//
// About window
//
void MainWindow::about()
{
/*	QString str= \
	tr("<b>QAntenna</b><br>" \
	"<a href=\"http://qantenna.sf.net/\">http://qantenna.sf.net/</a><br>" \
	"A multiplatform antenna and radiation pattern analyzer<br><br>" \
	"<i>This program is distributed under the terms of the " \
	"<a href=\"http://www.gnu.org/licenses/gpl.txt\">GPL v2</a>&nbsp;</i><br><br>" \
	"<u>Authors</u>:" \
	"<table>" \
	"<tr><td>&nbsp;&nbsp;-</td><td>Lisandro Damián Nicanor Pérez Meyer<br>" \
	"<a href=\"mailto:perezmeyer@gmail.com\">perezmeyer@gmail.com</a></td></tr>" \
	"<tr><td>&nbsp;&nbsp;-</td><td>Gustavo Gonzalez<br>" \
	"<a href=\"mailto:gonzalgustavo@gmail.com\">gonzalgustavo@gmail.com</a></td></tr>" \
	"<tr><td>&nbsp;&nbsp;-</td><td>Pablo Odorico<br>" \
	"<a href=\"mailto:pablo.odorico@gmail.com\">pablo.odorico@gmail.com</a></td></tr>" \
	"</table><br>Icons by <a href=\"http://www.everaldo.com/\">Everaldo</a>.");

	QMessageBox::about(this, "About QAntenna", str);*/

	AboutWindow aboutWin;

	// We show the window
	aboutWin.exec();
}

void MainWindow::aboutQt()
{
	QApplication::aboutQt();
}

//
// Render to file/clipboard
//

bool MainWindow::snapshot(QPixmap &pixmap)
{
	QString text= "";
	QRegExp regExp(tr("([0-9]+) *x *([0-9]+)"));
	bool ok= true;

	while(ok && !regExp.exactMatch(text)) {
      text= QInputDialog::getText(this, tr("Render into file"),
		tr("Enter the desired resolution:"), QLineEdit::Normal,
		tr("%1 x %2").arg(renderWidth).arg(renderHeight), &ok);
    }
	if(!ok) return false;

	// Resolution
	int width= Camera::limit(regExp.cap(1).toInt(), 100, 2048);
	int height= Camera::limit(regExp.cap(2).toInt(), 100, 2048);

	// Store resolution
	renderWidth= width;
	renderHeight= height;

	QSize size(width, height);
	QSize oldSize= ui.widgetGL->size();

	pixmap= ui.widgetGL->snapshot(width, height);

	return true;
}

void MainWindow::renderToFile()
{
	QPixmap pixmap;
	if(!snapshot(pixmap)) return;

	// The following code is based on jpn's code from qtcenter.org

    // construct a filter of all supported formats by qt
    QString filter;
    QList<QByteArray> formats = QImageWriter::supportedImageFormats();

	// Put PNG format as first option
	if(formats.indexOf("png")) {
		filter += QString("PNG file (*.png);;");
		formats.removeAt(formats.indexOf("png"));
	}
	// Put rest of formats
    foreach(QString format, formats) {
        filter += QString(tr("%1 file (*.%2);;")).arg(format.toUpper()).arg(format);
    }
    // remove unnecessary chars from the end of the filter
    if(filter.endsWith(";;")) filter.chop(2);

	// get save file name
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Image As"), renderPath, filter, &selectedFilter);

    if (!fileName.isEmpty()) {
        // keep track of the current renderPath
        renderPath = QDir(fileName).path();

        // check for the selected format
        QString format = selectedFilter.split(" ").at(0);
        QFileInfo fi(fileName);
        if (!fi.suffix().endsWith(format, Qt::CaseInsensitive)) {
            // remove possible incorrect suffix
            fileName.chop(fi.suffix().length());
            // set correct suffix
            fileName += "." + format.toLower();
        }

        // save image in the selected format
		logStart("filesave.png", tr("Rendering to \"<font color=\"#000066\">")+
			DataManager::cleanPathName(renderPath)+"</font>\"... ");
        if(pixmap.save(fileName, format.toAscii().constData())) {
			logEndOK(true);
        } else {
			QMessageBox::information(this, "Error", QString(tr("Unable to save %1.")).arg(fileName));
			logEndOK(false);
		}
    }
}

void MainWindow::renderToClipboard()
{
	QPixmap pixmap;
	if(!snapshot(pixmap)) return;

	logStart("filesave.png", tr("Rendering to clipboard... "));
	QApplication::clipboard()->setPixmap(pixmap);
	logEndOK(true);
}
