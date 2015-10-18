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

#include "LyricsSection.h"

#include "tu_LyricsSection.h"

void TuLyricsSection::construct()
{
    LyricsSection *pSection;

    pSection = new LyricsSection();
    QVERIFY(pSection != NULL);
    QCOMPARE(pSection->text(), QString(""));

    delete pSection;
}

void TuLyricsSection::setText_data()
{
    QTest::addColumn<QString>("rawText");
    QTest::addColumn<int>("status");
    QTest::addColumn<QString>("strippedText");
    QTest::addColumn<QString>("htmlText");
    QTest::addColumn<QString>("titleText");

    QTest::newRow("empty") << "" << -1 << "" << "" << "";
    QTest::newRow("one line - no tags") << "some text" << -1 << "some text" << "some text" << "some text";
    QTest::newRow("multi line - no tags") << "some text\nmore text" << -1 << "some text\nmore text"
                                          << "some text\nmore text" << "some text";
    QTest::newRow("one line - bold tag") << "some [b]bold[/b] text" << -1 << "some bold text"
                                         << "some <b>bold</b> text" << "some bold text";
}

void TuLyricsSection::setText()
{
    QFETCH(QString, rawText);
    QFETCH(int, status);
    QFETCH(QString, strippedText);
    QFETCH(QString, htmlText);
    QFETCH(QString, titleText);

    LyricsSection *pSection;

    pSection = new LyricsSection();
    QVERIFY(pSection != NULL);

    QCOMPARE(pSection->setText(rawText), status);

    QCOMPARE(pSection->text(), rawText);
    QCOMPARE(pSection->strippedText(), strippedText);
    QCOMPARE(pSection->htmlText(), htmlText);
    QCOMPARE(pSection->titleText(), titleText);
}

QTEST_MAIN(TuLyricsSection)
