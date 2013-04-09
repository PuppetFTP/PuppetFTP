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

    // Network
    QString                           getServerName()                                                      const;
    void                              setServerName(const QString& name);
    QString                           getServerAddr()                                                      const;
    quint16                           getServerPort()                                                      const;
    void                              setServerPort(quint16 port);
    INTERNET_PROTOCOL::ip             getInternetProtocol()                                                const;
    void                              setInternetProtocol(INTERNET_PROTOCOL::ip ip);
    quint16                           getIdleTimeout()                                                     const;
    void                              setIdleTimeout(quint16 timeout);
    quint16                           getDataConnectionTimeout()                                           const;
    void                              setDataConnectionTimeout(quint16 timeout);

    // User
    bool                              isUsingSystemUser()                                                  const;
    void                              useSystemUser(bool use);
    bool                              isAnonymousAllowed()                                                 const;
    void                              allowAnonymous(bool allow);
    bool                              isAnonymousUploadAllowed()                                           const;
    void                              allowAnonymousUpload(bool allow);
    bool                              isAnonymousCreateDirAllowed()                                        const;
    void                              allowAnonymousCreateDir(bool allow);
    VIRTUAL_USER_AUTHENTICATION::auth getVirtualUserAuthentication()                                       const;
    void                              setVirtualUserAuthentication(VIRTUAL_USER_AUTHENTICATION::auth mode);
    void                              addVirtualUser(const QString& user, const QString& password);
    void                              remVirtualUser(const QString& user);
    QStringList                       virtualUsers()                                                       const;

    // Misc
    QString                           getWelcomeMessage()                                                  const;
    void                              setWelcomeMessage(const QString& message);

    // Log
    QString                           getLogFile()                                                         const;

    // Configuration
    void                              importConfiguration(const QString& configuration);
    QString                           exportConfiguration()                                                const;
    void                              resetConfiguration();

    // Start/stop
    void                              start()                                                              const;
    void                              stop()                                                               const;
    void                              restart()                                                            const;
};

} // Impl
} // CORBA

#endif // SERVICECLIENTADAPTER_H_
