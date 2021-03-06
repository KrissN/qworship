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

#include <QtCore/QRegularExpression>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

#include "LyricsSection.h"

static const QRegularExpression bbStripRe = QRegularExpression(QStringLiteral("\\[[^\\]]*\\]"));

class InternalTextParseException
{
public:
    InternalTextParseException(QString::const_iterator pos, QString msg)
        : pos(pos), msg(msg)
        {};
    QString::const_iterator pos;
    QString msg;
};

LyricsSection::LyricsSection()
{
}

LyricsSection::LyricsSection(QString text, QString label, SectionFlags flags)
    : mText(text), mLabel(label), mFlags(flags)
{
    setText(mText);
}

LyricsSection::~LyricsSection()
{
}

void LyricsSection::setText(QString text)
{
    QString str = text;

    // Remove the BBCode tags
    str.remove(bbStripRe);    // http://stackoverflow.com/a/6000937

    // Prepare the HTML version. Replace all known BBCode tags with their HTML equivalents.
    // Read the contents inside the tag.
    QString::const_iterator it = text.begin();
    QString::const_iterator end = text.end();
    QString content;

    try
    {
        for ( ; it != end; it++)
        {
            QChar c = *it;
            if (c == '[')
            {
                it++;

                // Found an opening of a tag. This can be either the closure of the current tag or the
                // beginning of a new tag.
                if (*it == '/')
                {
                    // No tag closures at top level
                    throw InternalTextParseException(it, tr("Unmatched tag closure at top level"));
                }
                else
                {
                    // Found a nested tag. Make a recursive call to process it.
                    content += bbParseTag(it, end);
                }
            }
            else if (c == '\n')
            {
                content += "<br/>";
            }
            else
            {
                content += c;
            }
        }
        mText = text;
        mHtmlText = content;
        mStrippedText = str.split('\n', QString::SkipEmptyParts);
    }
    catch (InternalTextParseException & x)
    {
        qDebug() << "Error parsing text at offset " << x.pos - text.begin() << ": " << x.msg;
        throw TextParseException(x.pos - text.begin(), x.msg);
    }
}

QString LyricsSection::bbParseTag(QString::const_iterator & it, QString::const_iterator end) const
{
    QString tag;
    QString tagparam;
    QString content;

    // Upon entering the function the caller would have consumed the opening sqare bracket and
    // the iterator points to the first character of the tag name.

    // Read the rest of the tag
    for ( ; it != end; it++)
    {
        QChar c = *it;
        if (c == ']')
        {
            it++;
            break;
        }
        else if (!c.isLetterOrNumber() && (c != '='))
        {
            throw InternalTextParseException(it, tr("Invalid character in opening tag name: ") + c);
        }
        tag += c;
    }
    if (it == end)
    {
        // Reached end of string before tag close.
        throw InternalTextParseException(it, tr("Reached end of string before tag close"));
    }
    QStringList tagval = tag.split('=');
    tag = tagval[0];
    QString val;
    if (tagval.size() == 2)
    {
        val = tagval[1];
    }
    else if (tagval.size() > 2)
    {
        throw InternalTextParseException(it, tr("Incorrect tag parameter."));
    }


    QStringList htmlTags = bbTag2Html(it, tag, val);

    // Read the contents inside the tag.
    for ( ; it != end; it++)
    {
        QChar c = *it;
        if (c == '[')
        {
            it++;

            // Found an opening of a tag. This can be either the closure of the current tag or the
            // beginning of a new tag.
            if (*it == '/')
            {
                // This is a closure. Read the remaining tag and compare it to the starting tag.
                // They must match or otherwise the text is not correctly formatted.
                it++;
                QString tag2;
                for ( ; it != end; it++)
                {
                    c = *it;
                    if (c == ']')
                    {
                        break;
                    }
                    else if (!c.isLetterOrNumber())
                    {
                        throw InternalTextParseException(it, tr("Invalid character in closing tag name: ") + c);;
                    }
                    tag2 += c;
                }
                if (it == end)
                {
                    // Reached end of string before tag close.
                    throw InternalTextParseException(it, tr("Reached end of string before tag close"));
                }

                if (tag != tag2)
                {
                    throw InternalTextParseException(it, tr("Tag opening/closure mismatch"));
                }
                else
                {
                    return htmlTags[0] + content + htmlTags[1];
                }
            }
            else
            {
                // Found a nested tag. Make a recursive call to process it.
                content += bbParseTag(it, end);
            }
        }
        else if (c == '\n')
        {
            content += "<br/>";
        }
        else
        {
            content += c;
        }
    }

    // Reached end of string before tag close.
    throw InternalTextParseException(it, tr("Reached end of string before tag close"));
}

QStringList LyricsSection::bbTag2Html(QString::const_iterator & it, QString tag, QString arg) const
{
    if (tag.isEmpty())
    {
        throw InternalTextParseException(it, tr("Empty tag name"));
    }

    switch (tag[0].toLatin1()) {
        case 'b':
            if (tag == "b")
            {
                return QStringList() << QStringLiteral("<b>") << QStringLiteral("</b>");
            }
            break;
        case 'i':
            if (tag == "i")
            {
                return QStringList() << QStringLiteral("<i>") << QStringLiteral("</i>");
            }
            break;
        case 'u':
            if (tag == "u")
            {
                return QStringList() << QStringLiteral("<u>") << QStringLiteral("</u>");
            }
            break;
        case 'c':
            if (tag == "color")
            {
                if (arg.isEmpty())
                {
                    throw InternalTextParseException(it, tr("This tag requires an argument"));
                }
                return QStringList() << QStringLiteral("<span style=\"color: ") + arg + QStringLiteral("\">")
                                     << QStringLiteral("</span>");
            }
            break;
        case 's':
            if (tag == "size")
            {
                if (arg.isEmpty())
                {
                    throw InternalTextParseException(it, tr("This tag requires an argument"));
                }
                bool ok;
                int sizeval = arg.toInt(&ok);
                if (!ok || (sizeval > 9) || (sizeval < 1))
                {
                    throw InternalTextParseException(it, tr("Font size out of range (1-9)"));
                }

                // Convert the number to percentage. A value of 5 indicates 100%, 1 - 50%, 9 - 150%.
                uint sizeperc = 100 + ((sizeval - 5) * (50.0 / 4.0));

                return QStringList() << QStringLiteral("<span style=\"font-size: ") + QString::number(sizeperc) + QStringLiteral("%\">")
                                     << QStringLiteral("</span>");
            }
        default:
            break;
    }

    throw InternalTextParseException(it, tr("Unknown tag: ") + tag);
}

QString LyricsSection::tr(const char* pText)
{
    return qApp->translate("LyricsSection", pText);
}
