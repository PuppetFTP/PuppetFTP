/*
 * ServiceClientAdapter.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef SERVICECLIENTADAPTER_H_
#define SERVICECLIENTADAPTER_H_

#include <qglobal.h>
#include <QString>
#include <QVariant>
#include <QByteArray>
#include "ServerConfigHandler.hh"
#include "IServerConfigurationProvider.h"

namespace CORBA {
namespace Impl {

class ServiceClientAdapter : public IServerConfigurationProvider {
private:
    ServerConfigHandler_var _handler;

    ServiceClientAdapter();

public:
    ServiceClientAdapter(const ServerConfigHandler_var& handler);
    ~ServiceClientAdapter();

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

} // namespace Impl
} // namespace CORBA

#endif // SERVICECLIENTADAPTER_H_
