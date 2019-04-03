/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "productmodel.h"

#include <rest/restapi.h>
#include <rest/restclient.h>

#include <QNetworkReply>

using namespace KUserFeedback::Console;

ProductModel::ProductModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

ProductModel::~ProductModel() = default;

void ProductModel::setRESTClient(RESTClient* client)
{
    if (client != m_restClient)
        clear();
    Q_ASSERT(client);
    m_restClient = client;
    connect(m_restClient, &RESTClient::clientConnected, this, &ProductModel::reload);
    reload();
}

void ProductModel::clear()
{
    if (m_products.isEmpty())
        return;
    beginRemoveRows({}, 0, m_products.size() - 1);
    m_products.clear();
    endRemoveRows();
}

void ProductModel::reload()
{
    if (!m_restClient || !m_restClient->isConnected())
        return;

    auto reply = RESTApi::listProducts(m_restClient);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto json = reply->readAll();
            mergeProducts(Product::fromJson(json));
        }
	reply->deleteLater();
    });
}

int ProductModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_products.size();
}

QVariant ProductModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    switch (role) {
        case Qt::DisplayRole:
            return m_products.at(index.row()).name();
        case ProductRole:
            return QVariant::fromValue(m_products.at(index.row()));
    }
    return {};
}

QVariant ProductModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return tr("Products");
        }
    }
    return QAbstractListModel::headerData(section, orientation, role);
}

void ProductModel::mergeProducts(QVector<Product> &&products)
{
    std::sort(products.begin(), products.end(), [](const Product &lhs, const Product &rhs) {
        Q_ASSERT(lhs.isValid());
        Q_ASSERT(rhs.isValid());
        return lhs.name() < rhs.name();
    });

    auto newIt = products.cbegin();
    auto it = m_products.begin();

    while (it != m_products.end() && newIt != products.cend()) {
        const auto row = std::distance(m_products.begin(), it);
        if ((*newIt).name() < (*it).name()) {
            beginInsertRows({}, row, row);
            it = m_products.insert(it, (*newIt));
            endInsertRows();
            ++it;
            ++newIt;
        } else if ((*it).name() < (*newIt).name()) {
            beginRemoveRows({}, row, row);
            it = m_products.erase(it);
            endRemoveRows();
        } else {
            *it = *newIt;
            emit dataChanged(index(row, 0), index(row, 0));
            ++it;
            ++newIt;
        }
    }

    if (it == m_products.end() && newIt != products.cend()) { // trailing insert
        const auto count = std::distance(newIt, products.cend());
        beginInsertRows({}, m_products.size(), m_products.size() + count - 1);
        while (newIt != products.cend())
            m_products.push_back(*newIt++);
        endInsertRows();
    } else if (newIt == products.cend() && it != m_products.end()) { // trailing remove
        const auto start = std::distance(m_products.begin(), it);
        const auto end = m_products.size() - 1;
        beginRemoveRows({}, start, end);
        m_products.resize(start);
        endResetModel();
    }
}
