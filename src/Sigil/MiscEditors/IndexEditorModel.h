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
#ifndef INDEXEDITORMODEL_H
#define INDEXEDITORMODEL_H

#include <QtGui/QStandardItemModel>
#include <QDropEvent>

#include "Misc/SettingsStore.h"

class IndexEditorModel : public QStandardItemModel
{
     Q_OBJECT

public:
    IndexEditorModel(QObject *parent = 0);
    ~IndexEditorModel();

    static IndexEditorModel* instance();

    struct indexEntry {
        QString pattern;
        QString index_entry;
    };

    void ClearData();
    void LoadInitialData(QString filename = QString());
    void LoadData(QString filename = QString(), QStandardItem *parent_item = NULL);

    void AddFullNameEntry(IndexEditorModel::indexEntry *entry = NULL, QStandardItem *parent_item = NULL, int row = -1);

    QStandardItem* AddEntryToModel(IndexEditorModel::indexEntry *entry, bool is_group = false, QStandardItem *parent_item = NULL, int row = -1);

    QString SaveData(QList<IndexEditorModel::indexEntry*> entries = QList<IndexEditorModel::indexEntry*>(), QString filename = QString());

    QList<IndexEditorModel::indexEntry *> GetEntries(QList<QStandardItem*> items = QList<QStandardItem*>());
    IndexEditorModel::indexEntry* GetEntry(QStandardItem* item);

    QList<QStandardItem*> GetItems();

private:
    static IndexEditorModel *m_instance;
};

#endif // INDEXEDITORMODEL_H
