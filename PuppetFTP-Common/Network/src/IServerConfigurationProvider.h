/*
 * IServiceConfigurationProvider.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef ISERVERCONFIGURATIONPROVIDER_H_
#define ISERVERCONFIGURATIONPROVIDER_H_

#include <QMetaType>
#include <qglobal.h>
#include <QString>
#include <QStringList>

class IServerConfigurationProvider {
public:

	/** Internet protocol available **/
    typedef struct {
        enum ip { IPv4, IPv6, undefined };
    } INTERNET_PROTOCOL;

    /** User authentication mode **/
    typedef struct {
        enum auth { Anonymous };
    } VIRTUAL_USER_AUTHENTICATION;

    virtual ~IServerConfigurationProvider() {}

    /********************************************************************************/
    /** Network                                                                    **/
    /** Return the server name **/
    virtual QString                           getServerName()                                                      const = 0;
    /** Set the server name **/
    virtual void                              setServerName(const QString& name)                                         = 0;
    /** Return the server address. **/
    virtual QString                           getServerAddr()                                                      const = 0;
    /** Return the server port. **/
    virtual quint16                           getServerPort()                                                      const = 0;
    /** Set the server port **/
    virtual void                              setServerPort(quint16 port)                                                = 0;
    /** Return the internet protocol used by the server. **/
    virtual INTERNET_PROTOCOL::ip             getInternetProtocol()                                                const = 0;
    /** Set the internet protocol used by the server. **/
    virtual void                              setInternetProtocol(INTERNET_PROTOCOL::ip ip)                              = 0;
    /** Return the idle timeout value (seconds). **/
    virtual quint16                           getIdleTimeout()                                                     const = 0;
    /** Set the idle timeout (seconds). **/
    virtual void                              setIdleTimeout(quint16 timeout)                                            = 0;
    /** Return the data connection timeout (second). **/
    virtual quint16                           getDataConnectionTimeout()                                           const = 0;
    /** Set the data connection timeout (second). **/
    virtual void                              setDataConnectionTimeout(quint16 timeout)                                  = 0;

    /********************************************************************************/
    /** User                                                                       **/
    /** Return true if the server used system user. **/
    virtual bool                              isUsingSystemUser()                                                  const = 0;
    /** Enable/Disable authentication with system users. **/
    virtual void                              useSystemUser(bool use)                                                    = 0;
    /** Return true if connection as anonymous is allowed. **/
    virtual bool                              isAnonymousAllowed()                                                 const = 0;
    /** Enable/disable anonymous user. **/
    virtual void                              allowAnonymous(bool allow)                                                 = 0;
    /** Return true if the anonymous user is allowed to upload data. **/
    virtual bool                              isAnonymousUploadAllowed()                                           const = 0;
    /** Enable/disable the upload for anonymous user. **/
    virtual void                              allowAnonymousUpload(bool allow)                                           = 0;
    /** Return true if the anonymous user is allowed to create directories. **/
    virtual bool                              isAnonymousCreateDirAllowed()                                        const = 0;
    /** Enable/disable the creation of directories by the anonymous user. **/
    virtual void                              allowAnonymousCreateDir(bool allow)                                        = 0;
    /** Retrieve the current virtual user authentication mode. **/
    virtual VIRTUAL_USER_AUTHENTICATION::auth getVirtualUserAuthentication()                                       const = 0;
    /** Change the current virtual user authentication mode. **/
    virtual void                              setVirtualUserAuthentication(VIRTUAL_USER_AUTHENTICATION::auth mode)       = 0;
    /** Add a virtual user for the current virtual user authentication mode. **/
    virtual void                              addVirtualUser(const QString& user, const QString& password)               = 0;
    /** Remove a virtual user for the current virtual user authentication mode. **/
    virtual void                              remVirtualUser(const QString& user)                                        = 0;
    /** Retrieve the virtual user of the current virtual user authentication mode. **/
    virtual QStringList                       virtualUsers()                                                       const = 0;

    /********************************************************************************/
	/** Misc                                                                       **/
    /** Return the welcome message of this server. **/
    virtual QString                           getWelcomeMessage()                                                  const = 0;
    /** Set the welcome message of this server. **/
    virtual void                              setWelcomeMessage(const QString& message)                                  = 0;
    /** Return the path of the log file, only for informations. **/
    virtual QString                           getLogFile()                                                         const = 0;

    /********************************************************************************/
	/** Configuration                                                              **/
    /** Import a configuration on this server. **/
    virtual void                              importConfiguration(const QString& configuration)                          = 0;
    /** Export the current configuration. **/
    virtual QString                           exportConfiguration()                                                const = 0;
    /** Reset the configure to default. **/
    virtual void                              resetConfiguration()                                                       = 0;

    /********************************************************************************/
	/** Service management                                                         **/
    /** Start the server. **/
    virtual void                              start()                                                              const = 0;
    /** Stop the server. **/
    virtual void                              stop()                                                               const = 0;
    /** Restart the server. **/
    virtual void                              restart()                                                            const = 0;

};

Q_DECLARE_METATYPE(IServerConfigurationProvider::INTERNET_PROTOCOL::ip)
Q_DECLARE_METATYPE(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth)

#endif // ISERVERCONFIGURATIONPROVIDER_H_
