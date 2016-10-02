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

#include "restapi.h"
#include "restclient.h"

#include <core/product.h>
#include <core/survey.h>

using namespace UserFeedback::Analyzer;

QNetworkReply* RESTApi::listProducts(RESTClient *client)
{
    return client->get(QStringLiteral("products"));
}

QNetworkReply* RESTApi::createProduct(RESTClient *client, const Product &p)
{
    Q_ASSERT(p.isValid());
    return client->post(QStringLiteral("products"),  p.toJson());
}

QNetworkReply* RESTApi::updateProduct(RESTClient *client, const Product &p)
{
    Q_ASSERT(p.isValid());
    return client->put(QStringLiteral("products/") + p.name(), p.toJson());
}

QNetworkReply* RESTApi::deleteProduct(RESTClient *client, const Product &p)
{
    Q_ASSERT(p.isValid());
    return client->deleteResource(QStringLiteral("products/") + p.name());
}

QNetworkReply* RESTApi::listSurveys(RESTClient *client, const Product &p)
{
    Q_ASSERT(p.isValid());
    return client->get(QStringLiteral("surveys/") + p.name());
}

QNetworkReply* RESTApi::createSurvey(RESTClient *client, const Product &p, const Survey &s)
{
    Q_ASSERT(p.isValid());
    return client->post(QStringLiteral("surveys/") + p.name(), s.toJson());
}

QNetworkReply* RESTApi::updateSurvey(RESTClient *client, const Survey &s)
{
    return client->put(QStringLiteral("surveys/") + QString::number(s.id()), s.toJson());
}

QNetworkReply* RESTApi::deleteSurvey(RESTClient *client, const Survey &s)
{
    return client->deleteResource(QStringLiteral("surveys/") + QString::number(s.id()));
}
