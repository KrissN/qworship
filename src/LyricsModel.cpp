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

#include "LyricsModel.h"

LyricsModel::LyricsModel(QObject* pParent)
    : QAbstractItemModel(pParent)
{
}

LyricsModel::~LyricsModel()
{
}

QModelIndex LyricsModel::index(int row, int column, const QModelIndex & parent) const
{
    Q_UNUSED(parent); // unused for now

    return createIndex(row, column);
}

QModelIndex LyricsModel::parent(const QModelIndex & index) const
{
    Q_UNUSED(index); // unused for now

    return QModelIndex();
}

int LyricsModel::rowCount(const QModelIndex & parent) const
{
    if (parent.isValid())
    {
        // TODO: Temporary
        return 0;
    }
    else
    {
        return lyrics.count();
    }
}

int LyricsModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    // While models used for widget-type views primarily provide different
    // data fields by means of columns, QML models provide data fields using dedicated roles.
    // This means that the column count can be safely set to the minimum, which is 1.
    return 1;
}

QVariant LyricsModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}

QHash<int, QByteArray> LyricsModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names.insert(LyricsTitleRole, "title");
    names.insert(LyricsSectionTextRole, "text");

    return names;
}
