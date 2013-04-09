/*
 * ServiceAdapter.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef SERVICEADAPTER_H_
#define SERVICEADAPTER_H_

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

    // Network
    char*                                            getServerName();
    void                                             setServerName(const char* name);
    char*                                            getServerAddr();
    unsigned short                                   getServerPort();
    void                                             setServerPort(unsigned short port);
    ServerConfigHandler::INTERNET_PROTOCOL           getInternetProtocol();
    void                                             setInternetProtocol(ServerConfigHandler::INTERNET_PROTOCOL ip);
    unsigned short                                   getIdleTimeout();
    void                                             setIdleTimeout(unsigned short to);
    unsigned short                                   getDataConnectionTimeout();
    void                                             setDataConnectionTimeout(unsigned short);

    // User
    bool                                             isUsingSystemUser();
    void                                             useSystemUser(bool use);
    bool                                             isAnonymousAllowed();
    void                                             allowAnonymous(bool allow);
    bool                                             isAnonymousUploadAllowed();
    void                                             allowAnonymousUpload(bool allow);
    bool                                             isAnonymousCreateDirAllowed();
    void                                             allowAnonymousCreateDir(bool allow);
    ServerConfigHandler::VIRTUAL_USER_AUTHENTICATION getVirtualUserAuthentication();
    void                                             setVirtualUserAuthentication(ServerConfigHandler::VIRTUAL_USER_AUTHENTICATION mode);
    void                                             addVirtualUser(const char* user, const char* password);
    void                                             remVirtualUser(const char* user);
    ServerConfigHandler::StringSequence*             virtualUsers();

    // Misc
    char*                                            getWelcomeMessage();
    void                                             setWelcomeMessage(const char * msg);

    // Log
    char*                                            getLogFile();

    // Configuration
    void                                             importConfiguration(const char* configuration);
    char*                                            exportConfiguration();
    void                                             resetConfiguration();

    // Start/stop
    void                                             start();
    void                                             stop();
    void                                             restart();
};

} // Impl
} // CORBA

#endif // SERVICEADAPTER_H_
