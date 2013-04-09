/*
 * TestServerConfigProvider.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef TESTSERVERCONFIGPROVIDER_H_
#define TESTSERVERCONFIGPROVIDER_H_

#include "IServerConfigurationProvider.h"

#define TEST_SERVER_NAME "TestServer@127.0.0.1"

class TestServerConfigProvider: public IServerConfigurationProvider {
private:
    QString               _name;
    quint16               _port;
    INTERNET_PROTOCOL::ip _ip;
    quint16               _idleTimeout;
    quint16               _dataTimeout;
    bool                  _useSystemUser;
    bool                  _anonymousAllowed;
    bool                  _anonymousUpload;
    bool                  _anonymousCreateDir;
    QString               _bannedList;
    QString               _welcomeMessage;

public:
    TestServerConfigProvider();
    ~TestServerConfigProvider();

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

    // import/export
    void                              importConfiguration(const QString& configuration);
    QString                           exportConfiguration()                                                const;
    void                              resetConfiguration();

    // Start/stop
    void                              start()                                                              const;
    void                              stop()                                                               const;
    void                              restart()                                                            const;
};

#endif /* TESTSERVERCONFIGPROVIDER_H_ */
