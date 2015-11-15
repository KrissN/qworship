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

#include <QtCore/QString>
#include <QtCore/QList>

#include "LyricsSection.h"

class Lyrics
{
public:
    typedef QList<LyricsSection> LyricsSectionList;

    Lyrics();
    Lyrics(quint32 id, QList<LyricsSection> sections, QString title);
    ~Lyrics();

    quint32 id() const { return mId; };
    LyricsSectionList sections() { return mSections; };
    QString title() const;
private:
    quint32 mId;
    QString mTitle;
    LyricsSectionList mSections;

    static quint32 mMaxId;
};
