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

#include "tu_Lyrics.h"

void TuLyrics::construct()
{
    Lyrics *pLyrics;

    /* Step 1: Default constructor. */
    try
    {
        pLyrics = new Lyrics();
        QVERIFY(pLyrics != NULL);
        QVERIFY(pLyrics->sections().isEmpty());
        QCOMPARE(pLyrics->title(), QString());
        delete pLyrics;
    }
    catch (LyricsSection::TextParseException &)
    {
        QFAIL("Unexpected TextParseException thrown");
    }

    Lyrics::LyricsSectionList sectionList;
    sectionList.append(LyricsSection("test[b]1[/b]", "1", LyricsSection::NoLineWrap));
    QVERIFY(sectionList.size() == 1);
    
    /* Step 2: Parametrised constructor. */
    try
    {

        pLyrics = new Lyrics(123, sectionList, "test2");

        QCOMPARE(pLyrics->id(), 123u);
        QCOMPARE(pLyrics->sections()[0].text(), QString("test[b]1[/b]"));
        QCOMPARE(pLyrics->title(), QString("test2"));
        
        delete pLyrics;
    }
    catch (LyricsSection::TextParseException &)
    {
        QFAIL("Unexpected TextParseException thrown");
    }
}

QTEST_MAIN(TuLyrics)
