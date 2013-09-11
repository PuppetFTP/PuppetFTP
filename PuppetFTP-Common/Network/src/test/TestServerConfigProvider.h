/*
 * TestServerConfigProvider.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef TESTSERVERCONFIGPROVIDER_H_
#define TESTSERVERCONFIGPROVIDER_H_

#include <QString>
#include <QStringList>
#include <QVariant>
#include "IServerConfigurationProvider.h"

#define TEST_SERVER_NAME "TestServer@127.0.0.1"

class TestServerConfigProvider: public IServerConfigurationProvider {
private:
    QString _name;

public:
    TestServerConfigProvider();
    ~TestServerConfigProvider();

    bool loadPlugin(const QString & pluginId, const QString & pluginName);
    bool unloadPlugin(const QString & pluginId);

    bool set(const QString & pluginId, const QString & propertyName, const QVariant & value = QVariant());
    QVariant get(const QString & pluginId, const QString & propertyName);

    QVariant exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList = QVariantList());

    QStringList metaProperties(const QString & pluginId);
    QStringList metaTasks(const QString & pluginId);

    QString lastErrorString();
    bool hasFailure();
};

#endif /* TESTSERVERCONFIGPROVIDER_H_ */
