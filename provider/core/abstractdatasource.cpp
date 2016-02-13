/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>

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

#include "abstractdatasource.h"
#include "abstractdatasource_p.h"

using namespace UserFeedback;

AbstractDataSourcePrivate::AbstractDataSourcePrivate() = default;

AbstractDataSourcePrivate::~AbstractDataSourcePrivate() = default;

AbstractDataSource::AbstractDataSource() :
    d(new AbstractDataSourcePrivate)
{
}

AbstractDataSource::~AbstractDataSource()
{
    delete d;
}

Provider::StatisticsCollectionMode AbstractDataSource::collectionMode() const
{
    Q_ASSERT(d->mode != Provider::NoStatistics);
    if (d->mode == Provider::NoStatistics)
        return Provider::AllStatistics;
    return d->mode;
}

void AbstractDataSource::setCollectionMode(Provider::StatisticsCollectionMode mode)
{
    Q_ASSERT(mode != Provider::NoStatistics);
    d->mode = mode;
}
