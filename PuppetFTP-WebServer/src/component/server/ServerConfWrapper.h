/*
 * ServerConfWrapper.h
 *
 *  Created on: 6 janv. 2013
 *      Author: laplace
 */

#ifndef SERVERCONFWRAPPER_H_
#define SERVERCONFWRAPPER_H_

#include <QObject>
#include "IServerConfigurationProvider.h"

namespace UI {

/**
 * This class allows you to use a IServerConfigurationProvider with
 * the Qt's Meta Object System only for reading properties. This class
 * has been created in order to construct the UI Widgets in the same
 * way that the Model.
 *
 * This class does not inherit from IServerConfigurationProvider because
 * it must only allow property reading and does not need any behavioral
 * features.
 */
class ServerConfWrapper: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString                                                         server_name                    READ getServerName                  )
    Q_PROPERTY(QString                                                         server_addr                    READ getServerAddr                  )
    Q_PROPERTY(quint16                                                         server_port                    READ getServerPort                  )
    Q_PROPERTY(IServerConfigurationProvider::INTERNET_PROTOCOL::ip             internet_protocol              READ getInternetProtocol            )
    Q_PROPERTY(quint16                                                         idle_timeout                   READ getIdleTimeout                 )
    Q_PROPERTY(quint16                                                         data_timeout                   READ getDataConnectionTimeout       )
    Q_PROPERTY(bool                                                            use_system_user                READ isUsingSystemUser              )
    Q_PROPERTY(bool                                                            anonymous_allowed              READ isAnonymousAllowed             )
    Q_PROPERTY(bool                                                            anonymous_upload_allowed       READ isAnonymousUploadAllowed       )
    Q_PROPERTY(bool                                                            anonymouse_create_dir_allowed  READ isAnonymousCreateDirAllowed    )
    Q_PROPERTY(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth virtual_user_auth              READ getVirtualUserAuthentication   )
    Q_PROPERTY(QStringList                                                     virtual_users                  READ virtualUsers                   )
    Q_PROPERTY(QString                                                         welcome_message                READ getWelcomeMessage              )
    Q_PROPERTY(QString                                                         log_file                       READ getLogFile                     )

    Q_ENUMS(IServerConfigurationProvider::INTERNET_PROTOCOL::ip)
    Q_ENUMS(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth)

private:
    ServerConfWrapper();
    IServerConfigurationProvider* _provider;

public:
    ServerConfWrapper(IServerConfigurationProvider* provider);
    virtual ~ServerConfWrapper();

    // Network
    QString                                                         getServerName()                 const;
    QString                                                         getServerAddr()                 const;
    quint16                                                         getServerPort()                 const;
    IServerConfigurationProvider::INTERNET_PROTOCOL::ip             getInternetProtocol()           const;
    quint16                                                         getIdleTimeout()                const;
    quint16                                                         getDataConnectionTimeout()      const;
    // User
    bool                                                            isUsingSystemUser()             const;
    bool                                                            isAnonymousAllowed()            const;
    bool                                                            isAnonymousUploadAllowed()      const;
    bool                                                            isAnonymousCreateDirAllowed()   const;
    IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth getVirtualUserAuthentication()  const;
    QStringList                                                     virtualUsers()                  const;
    // Misc
    QString                                                         getWelcomeMessage()             const;
    // Log
    QString                                                         getLogFile()                    const;
};

} // namespace UI

#endif /* SERVERCONFWRAPPER_H_ */
