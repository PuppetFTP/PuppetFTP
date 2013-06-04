#ifndef PROFTPDCONFIG_H
#define PROFTPDCONFIG_H

#include "metaconfig.h"
#include "lasterror.h"
#include "proftpdparser.h"

class ProFtpdConfigHandler : public MetaConfig, public LastError
{
    Q_OBJECT

public:
    ProFtpdConfigHandler(const QString & serverName, const QString & serverAddr, const QString & fileName = DEFAULT_CONFIG_PROFTPD_FILE, const QString & serverBinPath = DEFAULT_BIN_PATH_PROFTPD);
    ~ProFtpdConfigHandler();

    // Network
    Q_PROPERTY(QString serverName READ getServerName WRITE setServerName)
    QString getServerName() const;
    void    setServerName(const QString & name);

    Q_PROPERTY(QString serverAddr READ getServerAddr)
    QString getServerAddr() const;

    Q_PROPERTY(quint16 serverPort READ getServerPort WRITE setServerPort)
    quint16 getServerPort();
    void    setServerPort(quint16 port);

    Q_PROPERTY(QString internetProtocol READ getInternetProtocol WRITE setInternetProtocol)
    QString getInternetProtocol();
    void setInternetProtocol(const QString & ip);

    Q_PROPERTY(quint16 idleTimeout READ getIdleTimeout WRITE setIdleTimeout)
    quint16 getIdleTimeout();
    void setIdleTimeout(quint16 timeout);

    Q_PROPERTY(quint16 dataConnectionTimeout READ getDataConnectionTimeout WRITE setDataConnectionTimeout)
    quint16 getDataConnectionTimeout();
    void setDataConnectionTimeout(quint16 timeout);

    // Anonymous User
    Q_PROPERTY(bool anonymousEnable READ isAnonymousAllowed WRITE allowAnonymous)
    bool isAnonymousAllowed();
    void allowAnonymous(bool allow);

    Q_PROPERTY(bool anonUploadEnable READ isAnonymousUploadAllowed WRITE allowAnonymousUpload)
    bool isAnonymousUploadAllowed();
    void allowAnonymousUpload(bool allow);

    Q_PROPERTY(bool anonMkdirWriteEnable READ isAnonymousMakeDirAllowed WRITE allowAnonymousMakeDir)
    bool isAnonymousMakeDirAllowed();
    void allowAnonymousMakeDir(bool allow);

    // Misc
    Q_PROPERTY(QString welcomeMessage READ getWelcomeMessage WRITE setWelcomeMessage)
    QString getWelcomeMessage();
    void setWelcomeMessage(const QString & message);

    // Log
    Q_PROPERTY(QString logFile READ getLogFile)
    QString getLogFile();

    // Start/stop
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void restart();

    //Parser
    Q_PROPERTY(QString parserFilename READ parserFileName WRITE setParserFileName)
    QString parserFileName();
    void setParserFileName(const QString filename);

    Q_PROPERTY(bool parserDryRun READ isParserDryRun WRITE setParserDryRun)
    bool isParserDryRun();
    void setParserDryRun(bool dryRun);

private:
    ProftpdParser m_parser;

    QString	m_serverName;
    QString	m_serverAddr;
    QString	m_serverPath;
    QString m_serviceName;
};

#endif // PROFTPDCONFIG_H
