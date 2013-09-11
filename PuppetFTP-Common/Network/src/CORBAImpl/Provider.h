/*
 * Provider.h
 *
 *  Created on: 27 mars 2012
 *      Author: Cedric Laplace
 */

#ifndef PROVIDER_H_
#define PROVIDER_H_

#include <string>
#include <QString>
#include <QMap>
#include <QThread>
#include "ServerConfigHandler.hh"
#include "INetworkAccessProvider.h"
#include "ServiceAdapter.h"

#define CONTEXT_NAME_ID     (const char*)"Server"
#define CONTEXT_NAME_KIND   (const char*)"ServerContext"
#define CONTEXT_OBJECT_KIND (const char*)"Object"

namespace CORBA {
namespace Impl {

class Provider : public INetworkAccessProvider, public QThread {
private:
    CORBA::ORB_var                 _orb;
    PortableServer::POA_var        _poa;
    CosNaming::NamingContext_var   _naming;
    QMap<QString, ServiceAdapter*> _handlers;

protected:
    void run();
    void bindObjectToName(const char* name, CORBA::Object_ptr objectRef);

public:
    Provider();
    virtual ~Provider();

    void configure(MODE::mode mode, const QMap<QString, QString>& options);
    void unconfigure();

    void registerServiceProvider(const QString& name, IServerConfigurationProvider* provider);
    void unregisterServiceProvider(const QString& name);

    IServerConfigurationProvider* getServiceClient(const QString& name);
};

} // Impl
} // CORBA

#endif // PROVIDER_H_
