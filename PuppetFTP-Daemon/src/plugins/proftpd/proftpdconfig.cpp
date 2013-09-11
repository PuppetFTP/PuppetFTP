#include "proftpdconfig.h"
#include "servicemanager.h"

ProFtpdConfigHandler::ProFtpdConfigHandler(const QString & serverName, const QString & serverAddr, const QString & fileName, const QString & serverBinPath)
    : m_parser(fileName), m_serverName(serverName), m_serverAddr(serverAddr), m_serverPath(serverBinPath), m_serviceName("proftpd")
{
}

ProFtpdConfigHandler::~ProFtpdConfigHandler()
{
}

/********************************************************************************/

QString ProFtpdConfigHandler::getServerName() const
{
    return m_serverName;
}

void    ProFtpdConfigHandler::setServerName(const QString & name)
{
    m_serverName = name;
}

// Network
QString ProFtpdConfigHandler::getServerAddr() const
{
    return m_serverAddr;
}

quint16 ProFtpdConfigHandler::getServerPort()
{
    return m_parser.get(QLatin1String("Port")).toUInt();
}

void    ProFtpdConfigHandler::setServerPort(quint16 port)
{
    m_parser.set(QLatin1String("Port"), QVariant(port));
}

QString ProFtpdConfigHandler::getInternetProtocol()
{
    bool isIpv6 = m_parser.get(QLatin1String("UseIPv6")).toString() == QLatin1String("on");

    if (isIpv6)
        return QLatin1String("Ipv6");

    return QLatin1String("Ipv4");
}

void ProFtpdConfigHandler::setInternetProtocol(const QString & ip)
{
    if (ip == QLatin1String("IPv6"))
        m_parser.set(QLatin1String("UseIPv6"), QVariant(QLatin1String("on")));
    else if (ip == QLatin1String("IPv4"))
        m_parser.set(QLatin1String("UseIPv6"), QVariant(QLatin1String("off")));
}

quint16 ProFtpdConfigHandler::getIdleTimeout()
{
    return m_parser.get(QLatin1String("TimeoutIdle")).toUInt();
}

void ProFtpdConfigHandler::setIdleTimeout(quint16 timeout)
{
    m_parser.set(QLatin1String("TimeoutIdle"), timeout);
}

quint16 ProFtpdConfigHandler::getDataConnectionTimeout()
{
    return m_parser.get(QLatin1String("TimeoutStalled")).toUInt();
}

void ProFtpdConfigHandler::setDataConnectionTimeout(quint16 timeout)
{
    m_parser.set(QLatin1String("TimeoutStalled"), timeout);
}

// Anonymous User
bool ProFtpdConfigHandler::isAnonymousAllowed()
{
    return  m_parser.get(QString("Anonymous /home/ftp#User")) == QString("ftp")
        && m_parser.get(QString("Anonymous /home/ftp#Group")) == QString("ftp")
        && m_parser.get(QString("Anonymous /home/ftp#UserAlias")) == QString("anonymous ftp")
    ;
}

void ProFtpdConfigHandler::allowAnonymous(bool allow)
{
    if (allow) {
        m_parser.set(QString("Anonymous /home/ftp#User"), QString("ftp"));
        m_parser.set(QString("Anonymous /home/ftp#Group"), QString("ftp"));
        m_parser.set(QString("Anonymous /home/ftp#UserAlias"), QString("anonymous ftp"));
    } else {
        m_parser.set(QString("Anonymous /home/ftp#User"), QString("ftp"), true);
        m_parser.set(QString("Anonymous /home/ftp#Group"), QString("ftp"), true);
        m_parser.set(QString("Anonymous /home/ftp#UserAlias"), QString("anonymous ftp"), true);
    }
}

bool ProFtpdConfigHandler::isAnonymousUploadAllowed()
{
    if (m_parser.get(QString("Anonymous /home/ftp#Limit WRITE#DenyAll")).isValid())
        return false;

    return true;
}

void ProFtpdConfigHandler::allowAnonymousUpload(bool allow)
{
    if (allow) {
        m_parser.set(QString("Anonymous /home/ftp#Limit WRITE"), QVariant(), true);
        m_parser.set(QString("Anonymous /home/ftp#Limit WRITE#AllowAll"));
    } else {
        m_parser.set(QString("Anonymous /home/ftp#Limit WRITE"), QVariant(), true);
        m_parser.set(QString("Anonymous /home/ftp#Limit WRITE#DenyAll"));
    }
}

bool ProFtpdConfigHandler::isAnonymousMakeDirAllowed()
{
    if (m_parser.get(QString("Anonymous /home/ftp#Limit MKD#DenyAll")).isValid())
        return false;

    return true;
}

void ProFtpdConfigHandler::allowAnonymousMakeDir(bool allow)
{
    if (allow) {
        m_parser.set(QString("Anonymous /home/ftp#Limit MKD"), QVariant(), true);
        m_parser.set(QString("Anonymous /home/ftp#Limit MKD#AllowAll"));
    } else {
        m_parser.set(QString("Anonymous /home/ftp#Limit MKD"), QVariant(), true);
        m_parser.set(QString("Anonymous /home/ftp#Limit MKD#DenyAll"));
    }
}

// Misc
QString ProFtpdConfigHandler::getWelcomeMessage()
{
    return m_parser.get(QLatin1String("DisplayLogin")).toString();
}

void ProFtpdConfigHandler::setWelcomeMessage(const QString & message)
{
    m_parser.set(QLatin1String("DisplayLogin"), QVariant(message));
}

// Log
QString ProFtpdConfigHandler::getLogFile()
{
    return m_parser.get(QLatin1String("ServerLog")).toString();
}

// Start/stop
void ProFtpdConfigHandler::start()
{
    ServiceManager::start(m_serviceName);
}

void ProFtpdConfigHandler::stop()
{
    ServiceManager::stop(m_serviceName);
}

void ProFtpdConfigHandler::restart()
{
    ServiceManager::restart(m_serviceName);
}

QString ProFtpdConfigHandler::parserFileName() const
{
    return m_parser.fileName();
}
void ProFtpdConfigHandler::setParserFileName(const QString & filename)
{
    m_parser.setFileName(filename);
}

bool ProFtpdConfigHandler::isParserDryRun() const
{
    return m_parser.isDryRun();
}

void ProFtpdConfigHandler::setParserDryRun(bool dryRun)
{
    m_parser.setDryRun(dryRun);
}

QString ProFtpdConfigHandler::parserData() const
{
    return m_parser.Data();
}

void ProFtpdConfigHandler::setParserData(const QString & data)
{
    m_parser.setData(data);
}

QString ProFtpdConfigHandler::parserLastError()
{
    return m_parser.lastError();
}
