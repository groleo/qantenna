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
#include "antennadelegate.h"
#include <QString>
#include <QItemDelegate>
#include <QWidget>
#include <QDoubleSpinBox>
#include <QModelIndex>
#include <QDebug>
#include <QPainter>

AntennaDelegate::AntennaDelegate(int frequencyColumn, int indexColumn,
                                 QObject *parent) : QItemDelegate(parent)
{
	this->frequencyColumn = frequencyColumn;
	this->indexColumn = indexColumn;
}

void AntennaDelegate::paint(QPainter *painter,
                            const QStyleOptionViewItem & option,
                            const QModelIndex &index) const
{
	painter->save();
	if (option.state & QStyle::State_Selected)
         painter->fillRect(option.rect, option.palette.highlight());

	if(index.column() == frequencyColumn)
	{
		double freq = index.model()->data(index, Qt::DisplayRole).toDouble();
		QString text = QString("%1 MHz").arg(freq,0,'f',2);

		if(option.state & QStyle::State_Selected)
  			painter->setPen(option.palette.highlightedText().color());
		else
			painter->setPen(QColor(0, 0, 136));
		painter->drawText(option.rect, Qt::AlignRight | Qt::AlignVCenter, text);
	}
	else
		QItemDelegate::paint(painter,option,index);
	painter->restore();
}

QWidget * AntennaDelegate::createEditor(QWidget * parent,
                                        const QStyleOptionViewItem &/*option*/,
                                        const QModelIndex &index) const
{
	// Are we editing the frequency?
	if(index.column() == frequencyColumn)
	{
		// We set the properties
		QDoubleSpinBox * frequencyEdit = new QDoubleSpinBox(parent);
		frequencyEdit->setAlignment(Qt::AlignRight);
		frequencyEdit->setDecimals(2);
		frequencyEdit->setMinimum(0.0);
		frequencyEdit->setSingleStep(0.01);
		frequencyEdit->setMaximum(20000000000.0);
		// When the editing is finished, changes must be commited
		connect(frequencyEdit,SIGNAL(editingFinished()),
		        this,SLOT(commitAndCloseEditor()));
		return frequencyEdit;
	}
	else
	/*
		If you happen to want the rest of the cells in the item to be editable,
		uncomment the following and comment the other return.
	*/
// 		return QItemDelegate::createEditor(parent,option,index);
		return 0;
}

void AntennaDelegate::setEditorData(QWidget * editor,
                                    const QModelIndex & index) const
{
	if(index.column() == frequencyColumn)
	{
		QString temp = index.model()->data(index,Qt::DisplayRole).toString();
		temp.remove("MHz");
		double freq = temp.toDouble();
		QDoubleSpinBox * frequencyEdit = qobject_cast<QDoubleSpinBox *>(editor);
		frequencyEdit->setValue(freq);
	}
	else
		QItemDelegate::setEditorData(editor,index);
}

void AntennaDelegate::setModelData(QWidget * editor,
                                   QAbstractItemModel * model,
                                   const QModelIndex & index) const
{
	if(index.column() == frequencyColumn)
	{
		QDoubleSpinBox * frequencyEdit = qobject_cast<QDoubleSpinBox *>(editor);
		double freq = frequencyEdit->value();
		model->setData(index, freq);
	}
	else
		QItemDelegate::setModelData(editor,model,index);
}

void AntennaDelegate::commitAndCloseEditor()
{
	QDoubleSpinBox * editor = qobject_cast<QDoubleSpinBox *>(sender());
	// Commit data to the QTreeWidget
	emit commitData(editor);
	// Close the editor
	emit closeEditor(editor);
}

