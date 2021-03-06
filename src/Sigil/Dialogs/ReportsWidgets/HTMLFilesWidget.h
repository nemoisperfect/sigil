/************************************************************************
**
**  Copyright (C) 2012 John Schember <john@nachtimwald.com>
**  Copyright (C) 2012 Dave Heiland
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#pragma once
#ifndef HTMLFILESWIDGET_H
#define HTMLFILESWIDGET_H

#include <QtCore/QHash>
#include <QtGui/QDialog>
#include <QtGui/QStandardItemModel>
#include <QtCore/QSharedPointer>

#include "ResourceObjects/Resource.h"
#include "BookManipulation/Book.h"
#include "ReportsWidget.h"

#include "ui_ReportsHTMLFilesWidget.h"

class QString;
class QStringList;

class HTMLFilesWidget : public ReportsWidget

{
    Q_OBJECT

public:
    HTMLFilesWidget(QList<Resource*> html_resources, QSharedPointer<Book> book);

    void SetupTable(int sort_column = 1, Qt::SortOrder sort_order = Qt::AscendingOrder);

    QString saveSettings();

private slots:
    void Sort(int logicalindex, Qt::SortOrder order);

    void FilterEditTextChangedSlot(const QString &text);

    void Done();

private:
    void connectSignalsSlots();

    QList<Resource*> m_HTMLResources;

    QSharedPointer< Book > m_Book;

    QStandardItemModel *m_ItemModel;

    Ui::HTMLFilesWidget ui;
};

#endif // HTMLFILESWIDGET_H
