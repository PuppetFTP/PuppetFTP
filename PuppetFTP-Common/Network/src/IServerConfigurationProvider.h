/*
 * IServiceConfigurationProvider.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef ISERVERCONFIGURATIONPROVIDER_H_
#define ISERVERCONFIGURATIONPROVIDER_H_

#include <qglobal.h>
#include <QString>
#include <QVariant>

class IServerConfigurationProvider {
public:
	virtual ~IServerConfigurationProvider() {}

    virtual bool loadPlugin(const QString & pluginId, const QString & pluginName) = 0;
    virtual bool unloadPlugin(const QString & pluginId) = 0;

    virtual bool set(const QString & pluginId, const QString & propertyName, const QVariant & value = QVariant()) = 0;
    virtual QVariant get(const QString & pluginId, const QString & propertyName) = 0;

    virtual QVariant exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList = QVariantList()) = 0;

    virtual QStringList metaProperties(const QString & pluginId) = 0;
    virtual QStringList metaTasks(const QString & pluginId) = 0;

    virtual QString lastErrorString() = 0;
    virtual bool hasFailure() = 0;
};

#endif // ISERVERCONFIGURATIONPROVIDER_H_
