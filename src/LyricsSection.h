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

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

class LyricsSection : public QObject
{
    Q_OBJECT
public:
    enum SectionFlags
    {
        // By default the section lines are wrapped in case doing so makes it possible
        // to use a larger font for the whole section (for ex. a section having four long lines would
        // would be displayed in small font with excess vertical space. Wrapping lines leads to more shorter
        // lines which allows more optimal layout.
        // This flag disables this optimisation.
        NoLineWrap = 0x0001,
        // Change default alignment from center to left
        LeftAlign = 0x0002
    };

    LyricsSection(QObject *pParent = 0);
    LyricsSection(QObject *pParent, QString text, QString label, SectionFlags flags);
    ~LyricsSection();

    QString text() const { return mText; };
    QString label() const { return mLabel; };
    SectionFlags flags() const { return mFlags; };

    // Returns the section text without any rich text markup
    QString strippedText() const { return mStrippedText.join('\n'); };
    // Returns the section title (i.e. first line)
    QString titleText() const { return (mStrippedText.count() > 0) ? mStrippedText[0] : QString(); };
    // Returns a rich text using HTML markup
    QString htmlText() const { return mHtmlText; };

    int setText(QString text);
private:
    // The section content.
    QString mText;
    // An optional label - could be used to indicate verse number or 'refrain'.
    QString mLabel;
    // Bitmask containing some optional flags, which may influence formatting or behaviour.
    SectionFlags mFlags;

    // Derived from mText - cached for better performance
    QStringList mStrippedText;
    QString mHtmlText;
    int parseErrorChar;

    QString bbParseTag(QString::const_iterator & it, QString::const_iterator end) const;
    QStringList bbTag2Html(QString tag) const;
};

