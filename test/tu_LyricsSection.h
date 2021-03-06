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

#include <QtTest/QtTest>

class TuLyricsSection : public QObject
{
    Q_OBJECT
private slots:
    /**
     *  @brief  LyricsSection construction test.
     *
     *  Constructs a LyricsSection object and verifies that the new object has the expected
     *  properties.
     */
    void construct();

    /**
     *  @brief  LyricsSection text setting test.
     *
     *  Attempts to set various text to the lyrics section verifying the expected status code
     *  and all of the text-related properties (raw, HTML, stripped and title text).
     */
    void setText();
    void setText_data();

    /**
     *  @brief  Invalid text setting test.
     *
     *  Verifies that setting an invalid text preserves the text that was set previously.
     */
    void setBadText();
};
