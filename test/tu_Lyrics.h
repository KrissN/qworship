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

class TuLyrics : public QObject
{
    Q_OBJECT
private slots:
    /**
     *  @brief  Lyrics construction test.
     *
     *  Constructs a Lyrics object and verifies that the new object has the expected
     *  properties.
     */
    void construct();
};
