/*
    SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#ifndef KUSERFEEDBACK_QMLPROVIDEREXTENSION_H
#define KUSERFEEDBACK_QMLPROVIDEREXTENSION_H

#include "qmlabstractdatasource.h"

#include <QObject>
#include <QQmlListProperty>
#include <QVector>

namespace KUserFeedback {

class QmlProviderExtension : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<KUserFeedback::QmlAbstractDataSource> sources READ sources)
    Q_CLASSINFO("DefaultProperty", "sources")

public:
    explicit QmlProviderExtension(QObject *parent = nullptr);
    ~QmlProviderExtension();

    QQmlListProperty<QmlAbstractDataSource> sources();

private:
    static void sourceAppend(QQmlListProperty<QmlAbstractDataSource> *prop, QmlAbstractDataSource *value);
    static int sourceCount(QQmlListProperty<QmlAbstractDataSource> *prop);
    static QmlAbstractDataSource* sourceAt(QQmlListProperty<QmlAbstractDataSource> *prop, int index);
    static void sourceClear(QQmlListProperty<QmlAbstractDataSource> *prop);

    QVector<QmlAbstractDataSource*> m_sourceWrappers;
};

}

#endif // KUSERFEEDBACK_QMLPROVIDEREXTENSION_H
