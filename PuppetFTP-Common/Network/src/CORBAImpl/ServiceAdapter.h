/*
 * ServiceAdapter.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef SERVICEADAPTER_H_
#define SERVICEADAPTER_H_

#include <QVariant>
#include <QByteArray>
#include "ServerConfigHandler.hh"
#include "IServerConfigurationProvider.h"


namespace CORBA {
namespace Impl {

class ServiceAdapter : public POA_ServerConfigHandler {
private:
    ServiceAdapter();

    IServerConfigurationProvider* _configurator;

public:
    ServiceAdapter(IServerConfigurationProvider* configurator);
    virtual ~ServiceAdapter();

    ::CORBA::Boolean loadPlugin(const char* pluginId, const char* pluginName);
    ::CORBA::Boolean unloadPlugin(const char* pluginId);
    ::CORBA::Boolean set(const char* pluginId, const char* propertyName, const ::ServerConfigHandler::ByteSequence& value);
    ServerConfigHandler::ByteSequence* get(const char* pluginId, const char* propertyName);
    ServerConfigHandler::ByteSequence* exec(const char* pluginId, const char* taskName, const ::ServerConfigHandler::ByteSequence& argumentList);
    ServerConfigHandler::StringSequence* metaProperties(const char* pluginId);
    ServerConfigHandler::StringSequence* metaTasks(const char* pluginId);
    char* lastErrorString();
    ::CORBA::Boolean hasFailure();
};

} // namespace Impl
} // namesapce CORBA

#endif // SERVICEADAPTER_H_
