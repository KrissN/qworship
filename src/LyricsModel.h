/**************************************************************************
 *
 *  This file is part of QWorship.
 *
 *  QWorship is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QWorship is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with QWorship. If not, see <http://www.gnu.org/licenses/>.
 *
 *************************************************************************/

#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>

#include "Lyrics.h"

class LyricsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum {
        LyricsTitleRole = Qt::UserRole,
        LyricsSectionTextRole,
        SortRole,
        FilterRole
    } LyricsCustomRole;

    LyricsModel(QObject* pParent = 0);
    virtual ~LyricsModel();
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Lyrics> lyrics;
};
