#ifndef VSFTPCONFIG_H
# define VSFTPCONFIG_H

#include "abstractauthentication.h"
#include "vsftpdparser.h"
#include "servicemanager.h"
#include "metaconfig.h"
#include "lasterror.h"

class VsftpdConfigHandler : public MetaConfig, public LastError
{
public:
    VsftpdConfigHandler(const QString & serverName, const QString & serverAddr, const QString & fileName = DEFAULT_CONFIG_VSFTP_FILE, const QString & serverBinPath = DEFAULT_BIN_PATH_VSFTP);
    ~VsftpdConfigHandler();

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
    Q_PROPERTY(bool anonymousEnable READ isAnonymousEnabled WRITE enableAnonymous)
    bool isAnonymousEnabled();
    void enableAnonymous(bool allow);

    QString anonymousRoot();
    void setAnonymousRoot(const QString & anonymousRoot);

    Q_PROPERTY(bool anonUploadEnable READ isAnonymousUploadEnabled WRITE enableAnonymousUpload)
    bool isAnonymousUploadEnabled();
    void enableAnonymousUpload(bool allow);

    Q_PROPERTY(bool writeEnable READ isWriteEnabled WRITE enableWrite)
    bool isWriteEnabled();
    void enableWrite(bool allow);

    Q_PROPERTY(bool anonWorldReadeable READ isAnonymousWorldReadable WRITE allowAnonymousWorldReadable)
    bool isAnonymousWorldReadable();
    void allowAnonymousWorldReadable(bool allow);

    Q_PROPERTY(bool anonOtherWriteEnable READ isAnonOtherWriteEnable WRITE enableAnonOtherWrite)
    bool isAnonOtherWriteEnable();
    void enableAnonOtherWrite(bool allow);

    Q_PROPERTY(bool anonMkdirWriteEnable READ isAnonymousMakeDirAllowed WRITE allowAnonymousMakeDir)
    bool isAnonymousMakeDirAllowed();
    void allowAnonymousMakeDir(bool allow);

    // Regular User
    Q_PROPERTY(bool localEnable READ isUsingSystemUser WRITE useSystemUser)
    bool isUsingSystemUser();
    void useSystemUser(bool use);

    Q_PROPERTY(bool chrootLocalUser READ isChrootLocalUser WRITE chrootLocalUser)
    bool isChrootLocalUser();
    void chrootLocalUser(bool use);

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
    QString parserFileName() const;
    void setParserFileName(const QString & filename);

    Q_PROPERTY(bool parserDryRun READ isParserDryRun WRITE setParserDryRun)
    bool isParserDryRun() const;
    void setParserDryRun(bool dryRun);

    Q_PROPERTY(QString parserData READ parserData WRITE setParserData)
    QString parserData() const;
    void setParserData(const QString & data);

    Q_PROPERTY(QString parserLastError READ parserLastError)
    QString parserLastError() const;

    // LastError
    Q_PROPERTY(QString lastError READ lastError)
    QString lastError() const;

private:
    VsftpdParser m_parser;

    QString m_serverName;
    QString m_serverAddr;
    QString m_serverPath;
    QString m_serviceName;
};

#endif // VSFTPCONFIG_H
