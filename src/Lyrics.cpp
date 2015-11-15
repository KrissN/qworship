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

#include "Lyrics.h"

quint32 Lyrics::mMaxId = 1;

Lyrics::Lyrics()
    : mId(mMaxId++)
{
}

Lyrics::Lyrics(quint32 id, QList<LyricsSection> sections, QString title)
    : mId(id), mTitle(title), mSections(sections)
{
    mMaxId = qMax(id, mMaxId);
}

Lyrics::~Lyrics()
{
}

QString Lyrics::title() const
{
    if (mTitle.isEmpty())
    {
        if (mSections.isEmpty())
        {
            return QStringLiteral("");
        }
        else
        {
            return mSections[0].titleText();
        }
    }
    else
    {
        return mTitle;
    }
}
