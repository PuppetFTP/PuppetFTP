#include <QProcess>
#include <iostream>
#include <QFile>

#include "proftpdconfig.h"

#include "CommunicationException.h"

ProFtpdConfigHandler::ProFtpdConfigHandler(const QString & serverName, const QString & serverAddr, const QString & fileName, const QString & serverBinPath)
    : m_serverName(serverName), m_serverAddr(serverAddr), m_parser(fileName), m_serverPath(serverBinPath), m_serviceName("proftpd")
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

quint16 ProFtpdConfigHandler::getServerPort() const
{
    return m_parser.get(QLatin1String("Port")).toUInt();
}

void    ProFtpdConfigHandler::setServerPort(quint16 port)
{
    m_parser.set(QLatin1String("Port"), QVariant(port));
}

QString ProFtpdConfigHandler::getInternetProtocol() const
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

quint16 ProFtpdConfigHandler::getIdleTimeout() const
{
    return m_parser.get(QLatin1String("TimeoutIdle")).toUInt();
}

void ProFtpdConfigHandler::setIdleTimeout(quint16 timeout)
{
    m_parser.set(QLatin1String("TimeoutIdle"), timeout);
}

quint16 ProFtpdConfigHandler::getDataConnectionTimeout() const
{
    return m_parser.get(QLatin1String("TimeoutStalled")).toUInt();
}

void ProFtpdConfigHandler::setDataConnectionTimeout(quint16 timeout)
{
    m_parser.set(QLatin1String("TimeoutStalled"), timeout);
}

// User
/*
bool ProFtpdConfigHandler::isUsingSystemUser() const
{
    /*if (m_parser.get(QLatin1String("local_enable")).toString() == QLatin1String("YES"))
        return true;
*//*
    return false;
}

void ProFtpdConfigHandler::useSystemUser(bool use)
{
    Q_UNUSED(use);
    //m_parser.set(QLatin1String("local_enable"), use ? QLatin1String("YES") : QLatin1String("NO"));
}

bool ProFtpdConfigHandler::isAnonymousAllowed() const
{
    return  m_parser.get(QString("Anonymous /home/ftp#User")) == QString("ftp")
        && m_parser.get(QString("Anonymous /home/ftp#Group")) == QString("nogroup")
        && m_parser.get(QString("Anonymous /home/ftp#UserAlias")) == QString("anonymous ftp")
    ;
}

void ProFtpdConfigHandler::allowAnonymous(bool allow)
{
    if (allow) {
        m_parser.set(QString("Anonymous /home/ftp#User"), QString("ftp"));
        m_parser.set(QString("Anonymous /home/ftp#Group"), QString("nogroup"));
        m_parser.set(QString("Anonymous /home/ftp#UserAlias"), QString("anonymous ftp"));
    } else {
        m_parser.set(QString("Anonymous /home/ftp#User"), QString("ftp"), true);
        m_parser.set(QString("Anonymous /home/ftp#Group"), QString("nogroup"), true);
        m_parser.set(QString("Anonymous /home/ftp#UserAlias"), QString("anonymous ftp"), true);
    }
}

bool ProFtpdConfigHandler::isAnonymousUploadAllowed() const
{
    return m_parser.get(QString("Anonymous /home/ftp#Directory *#Limit WRITE#DenyAll")).isValid();
}

void ProFtpdConfigHandler::allowAnonymousUpload(bool allow)
{
    if (allow) {
        m_parser.set(QString("Anonymous /home/ftp#Directory *#Limit WRITE#DenyAll"));
    } else {
        m_parser.set(QString("Anonymous /home/ftp#Directory *#Limit WRITE#DenyAll"), QVariant(), false);
    }
}

bool ProFtpdConfigHandler::isAnonymousCreateDirAllowed() const
{
    return isAnonymousUploadAllowed();
}

void ProFtpdConfigHandler::allowAnonymousCreateDir(bool allow)
{
    allowAnonymousUpload(allow);
}
*/
// Virtual User Management
/*
void ProFtpdConfigHandler::setVirtualUserAuthentication(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth mode)
{
    Q_UNUSED(mode);
}

IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth ProFtpdConfigHandler::getVirtualUserAuthentication() const
{
    return IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::Anonymous;
}

void ProFtpdConfigHandler::addVirtualUser(const QString & user, const QString & password)
{
    Q_UNUSED(user);
    Q_UNUSED(password);
  //  m_authentificator->addUser(QLatin1String(user), QLatin1String(password));
}

void ProFtpdConfigHandler::remVirtualUser(const QString & user)
{
    Q_UNUSED(user);
   // m_authentificator->removeUser(QLatin1String(user));
}

QStringList ProFtpdConfigHandler::virtualUsers() const
{
    return QStringList();
}
*/
// Misc
QString ProFtpdConfigHandler::getWelcomeMessage() const
{
    return m_parser.get(QLatin1String("DisplayLogin")).toString();
}

void ProFtpdConfigHandler::setWelcomeMessage(const QString & message)
{
    m_parser.set(QLatin1String("DisplayLogin"), QVariant(message));
}

// Log
QString ProFtpdConfigHandler::getLogFile() const
{
    return m_parser.get(QLatin1String("ServerLog")).toString();
}

// Start/stop
void ProFtpdConfigHandler::start() const
{
    int exitStatus = ServiceManager::start(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
}

void ProFtpdConfigHandler::stop() const
{
    int exitStatus = ServiceManager::stop(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
}

void ProFtpdConfigHandler::restart() const
{
    int exitStatus = ServiceManager::restart(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
 }
/*
QString ProFtpdConfigHandler::exportConfiguration() const
{
    QFile file(m_parser.filename());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::string err("Unable to access configuration file.");
        std::cerr << err << std::endl;
        throw CommunicationException(err.c_str());
    }

    QTextStream in(&file);
    QString data = in.readAll();

    file.close();

    return data;
}

void ProFtpdConfigHandler::importConfiguration(const QString & configuration)
{
    QFile file(m_parser.filename());

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        std::string err("Unable to access configuration file.");
        std::cerr << err << std::endl;
        throw CommunicationException(err.c_str());
    }

    QTextStream out(&file);
    out << configuration;

    file.close();
}

void ProFtpdConfigHandler::resetConfiguration()
{
}
*/
