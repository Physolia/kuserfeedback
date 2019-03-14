/*
    Copyright (C) 2017 Volker Krause <vkrause@kde.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "styleinfosource.h"

#include <QApplication>
#include <QPalette>
#include <QStyle>
#include <QVariant>

using namespace KUserFeedback;

StyleInfoSource::StyleInfoSource()
    : AbstractDataSource(QStringLiteral("style"))
{
}

QString StyleInfoSource::description() const
{
    return tr("The widget style used by the application, and information about the used color scheme.");
}

QVariant StyleInfoSource::data()
{
    QVariantMap m;
    if (qApp && qApp->style())
        m.insert(QStringLiteral("style"), qApp->style()->objectName()); // QStyleFactory sets the object name to the style name
    m.insert(QStringLiteral("dark"), qApp->palette().color(QPalette::Background).lightness() < 128);
    return m;
}

QString StyleInfoSource::name() const
{
    return tr("Application style");
}
