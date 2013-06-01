#ifndef PROFTPDCONFIG_H
#define PROFTPDCONFIG_H

#include "abstractauthentication.h"
#include "proftpdparser.h"
#include "servicemanager.h"

#include "metaconfig.h"

class Fules
{
public:
    Fules() {}
};

class ProFtpdConfigHandler : public MetaConfig, public Fules
{
    Q_OBJECT

public:
    ProFtpdConfigHandler(const QString & serverName, const QString & serverAddr, const QString & fileName = DEFAULT_CONFIG_PROFTPD_FILE, const QString & serverBinPath = DEFAULT_BIN_PATH_PROFTPD);
    ~ProFtpdConfigHandler();

    // Network
    Q_PROPERTY(QString serverName READ getServerName WRITE setServerName)
    Q_PROPERTY(QString serverAddr READ getServerAddr)
    Q_PROPERTY(quint16 serverPort READ getServerPort WRITE setServerPort)
    Q_PROPERTY(QString internetProtocol READ getInternetProtocol WRITE setInternetProtocol)
    Q_PROPERTY(quint16 idleTimeout READ getIdleTimeout WRITE setIdleTimeout)
    Q_PROPERTY(quint16 dataConnectionTimeout READ getDataConnectionTimeout WRITE setDataConnectionTimeout)

    QString getServerName() const;
    void    setServerName(const QString & name);
    QString getServerAddr() const;
    quint16 getServerPort() const;
    void    setServerPort(quint16 port);
    QString getInternetProtocol() const;
    void setInternetProtocol(const QString & ip);
    quint16 getIdleTimeout() const;
    void setIdleTimeout(quint16 timeout);
    quint16 getDataConnectionTimeout() const;
    void setDataConnectionTimeout(quint16 timeout);

    // User
    /*
    bool isUsingSystemUser() const;
    void useSystemUser(bool use);
    bool isAnonymousAllowed() const;
    void allowAnonymous(bool allow);
    bool isAnonymousUploadAllowed() const;
    void allowAnonymousUpload(bool allow);
    bool isAnonymousCreateDirAllowed() const;
    void allowAnonymousCreateDir(bool allow);
*/
    // Virtual User Management
/*
    void setVirtualUserAuthentication(VIRTUAL_USER_AUTHENTICATION::auth mode);
    VIRTUAL_USER_AUTHENTICATION::auth getVirtualUserAuthentication() const;
    void addVirtualUser(const QString & user, const QString & password);
    void remVirtualUser(const QString & user);
    QStringList virtualUsers() const;
*/
    // Misc
    Q_PROPERTY(QString welcomeMessage READ getWelcomeMessage WRITE setWelcomeMessage)

    QString getWelcomeMessage() const;
    void setWelcomeMessage(const QString & message);

    // Log
    Q_PROPERTY(QString logFile READ getLogFile)

    QString getLogFile() const;

    // Start/stop
    Q_INVOKABLE void start() const;
    Q_INVOKABLE void stop() const;
    Q_INVOKABLE void restart() const;

    // fichier de conf
/*
    QString exportConfiguration() const;
    void importConfiguration(const QString &configuration);
    void resetConfiguration();
*/
private:
    QString	m_serverName;
    QString	m_serverAddr;
    ProftpdParser m_parser;
    QString	m_serverPath;
    QString m_serviceName;
    AbstractAuthentication * m_authentificator;
};

#endif // PROFTPDCONFIG_H
