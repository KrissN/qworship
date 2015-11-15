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

    /* Step 1: Default constructor. */
    pSection = new LyricsSection();
    QVERIFY(pSection != NULL);
    QCOMPARE(pSection->text(), QString(""));

    delete pSection;

    /* Step 2: Parametrised constructor. */
    pSection = new LyricsSection(NULL, "test[b]1[/b]", "1", LyricsSection::NoLineWrap);
    QVERIFY(pSection != NULL);
    QCOMPARE(pSection->text(), QString("test[b]1[/b]"));
    QCOMPARE(pSection->strippedText(), QString("test1"));
    QCOMPARE(pSection->htmlText(), QString("test<b>1</b>"));
    QCOMPARE(pSection->titleText(), QString("test1"));
    QCOMPARE(pSection->label(), QString("1"));
    QCOMPARE(pSection->flags(), LyricsSection::NoLineWrap);

    /* Step 2: Parametrised constructor - negative case. */
    pSection = new LyricsSection(NULL, "test1[/b]", "1", LyricsSection::NoLineWrap);
    QVERIFY(pSection != NULL);
    QCOMPARE(pSection->text(), QString(""));
    QCOMPARE(pSection->strippedText(), QString(""));
    QCOMPARE(pSection->htmlText(), QString(""));
    QCOMPARE(pSection->titleText(), QString(""));
    QCOMPARE(pSection->label(), QString("1"));
    QCOMPARE(pSection->flags(), LyricsSection::NoLineWrap);

    delete pSection;
}

void TuLyricsSection::setText_data()
{
    QTest::addColumn<QString>("rawText");
    QTest::addColumn<int>("status");
    QTest::addColumn<QString>("strippedText");
    QTest::addColumn<QString>("htmlText");
    QTest::addColumn<QString>("titleText");

    QTest::newRow("empty")
        << ""
        << -1
        << ""
        << ""
        << "";
    QTest::newRow("one line - no tags")
        << "some text"
        << -1
        << "some text"
        << "some text"
        << "some text";
    QTest::newRow("multi line - no tags")
        << "some text\nmore text"
        << -1
        << "some text\nmore text"
        << "some text<br/>more text"
        << "some text";
    QTest::newRow("one line - bold tag")
        << "some [b]bold[/b] text"
        << -1
        << "some bold text"
        << "some <b>bold</b> text"
        << "some bold text";
    QTest::newRow("one line - italic tag")
        << "some [i]italic[/i] text"
        << -1
        << "some italic text"
        << "some <i>italic</i> text"
        << "some italic text";
    QTest::newRow("one line - underline tag")
        << "some [u]underline[/u] text"
        << -1
        << "some underline text"
        << "some <u>underline</u> text"
        << "some underline text";
    QTest::newRow("one line - red colour tag")
        << "some [color=red]red[/color] text"
        << -1
        << "some red text"
        << "some <span style=\"color: red\">red</span> text"
        << "some red text";
    QTest::newRow("one line - colour tag without argument")
        << "some [color]red[/color] text"
        << 12
        << ""
        << ""
        << "";
    QTest::newRow("one line - text size 10")
        << "some [size=10]large[/size] text"
        << 14
        << ""
        << ""
        << "";
    QTest::newRow("one line - text size 9")
        << "some [size=9]large[/size] text"
        << -1
        << "some large text"
        << "some <span style=\"font-size: 150%\">large</span> text"
        << "some large text";
    QTest::newRow("one line - text size 8")
        << "some [size=8]large[/size] text"
        << -1
        << "some large text"
        << "some <span style=\"font-size: 137%\">large</span> text"
        << "some large text";
    QTest::newRow("one line - text size 7")
        << "some [size=7]large[/size] text"
        << -1
        << "some large text"
        << "some <span style=\"font-size: 125%\">large</span> text"
        << "some large text";
    QTest::newRow("one line - text size 6")
        << "some [size=6]large[/size] text"
        << -1
        << "some large text"
        << "some <span style=\"font-size: 112%\">large</span> text"
        << "some large text";
    QTest::newRow("one line - text size 5 (normal)")
        << "some [size=5]normal[/size] text"
        << -1
        << "some normal text"
        << "some <span style=\"font-size: 100%\">normal</span> text"
        << "some normal text";
    QTest::newRow("one line - text size 4")
        << "some [size=4]small[/size] text"
        << -1
        << "some small text"
        << "some <span style=\"font-size: 87%\">small</span> text"
        << "some small text";
    QTest::newRow("one line - text size 3")
        << "some [size=3]small[/size] text"
        << -1
        << "some small text"
        << "some <span style=\"font-size: 75%\">small</span> text"
        << "some small text";
    QTest::newRow("one line - text size 2")
        << "some [size=2]small[/size] text"
        << -1
        << "some small text"
        << "some <span style=\"font-size: 62%\">small</span> text"
        << "some small text";
    QTest::newRow("one line - text size 1")
        << "some [size=1]small[/size] text"
        << -1
        << "some small text"
        << "some <span style=\"font-size: 50%\">small</span> text"
        << "some small text";
    QTest::newRow("one line - text size 0")
        << "some [size=0]small[/size] text"
        << 13
        << ""
        << ""
        << "";
    QTest::newRow("one line - text without size")
        << "some [size]small[/size] text"
        << 11
        << ""
        << ""
        << "";
    QTest::newRow("multi line - two tags")
        << "some [b]bold[/b] text\nmore [i]italic[/i] text"
        << -1
        << "some bold text\nmore italic text"
        << "some <b>bold</b> text<br/>more <i>italic</i> text"
        << "some bold text";
    QTest::newRow("multi line - break within tag")
        << "some [b]bold\nbold[/b] text"
        << -1
        << "some bold\nbold text"
        << "some <b>bold<br/>bold</b> text"
        << "some bold";
    QTest::newRow("one line - nested tags")
        << "some [b]bold [i]italic[/i][/b] text"
        << -1
        << "some bold italic text"
        << "some <b>bold <i>italic</i></b> text"
        << "some bold italic text";
    QTest::newRow("one line - invalid tag nesting")
        << "some [b]bold [i]italic[/b][/i] text"
        << 25
        << ""
        << ""
        << "";
    QTest::newRow("one line - no tag close")
        << "some [b]bold [i]italic[/i] text"
        << 31
        << ""
        << ""
        << "";
    QTest::newRow("one line - extra tag close")
        << "some bold italic[/i] text"
        << 17
        << ""
        << ""
        << "";

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

    if (status == -1)
    {
        QCOMPARE(pSection->text(), rawText);
    }
    else
    {
        QCOMPARE(pSection->text(), QString());
    }

    QCOMPARE(pSection->strippedText(), strippedText);
    QCOMPARE(pSection->htmlText(), htmlText);
    QCOMPARE(pSection->titleText(), titleText);
}

void TuLyricsSection::setBadText()
{
    LyricsSection *pSection = new LyricsSection();
    QVERIFY(pSection != NULL);

    QCOMPARE(pSection->setText("test[b]1[/b]"), -1);

    QCOMPARE(pSection->setText("test[/b]"), 5);

    QCOMPARE(pSection->text(), QString("test[b]1[/b]"));
    QCOMPARE(pSection->strippedText(), QString("test1"));
    QCOMPARE(pSection->htmlText(), QString("test<b>1</b>"));
    QCOMPARE(pSection->titleText(), QString("test1"));
}

QTEST_MAIN(TuLyricsSection)
