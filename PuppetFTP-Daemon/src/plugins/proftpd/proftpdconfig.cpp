#include <QDebug>
#include <QProcess>
#include <iostream>
#include <QFile>

#include "proftpdconfig.h"

#include "CommunicationException.h"

ProFtpdConfigProvider::ProFtpdConfigProvider(const QString & serverName, const QString & serverAddr, const QString & fileName, const QString & serverBinPath)
    : m_serverName(serverName), m_serverAddr(serverAddr), m_parser(fileName), m_serverPath(serverBinPath), m_serviceName("proftpd")
{
}

ProFtpdConfigProvider::~ProFtpdConfigProvider()
{
}

/********************************************************************************/

QString ProFtpdConfigProvider::getServerName() const
{
    return m_serverName;
}

void    ProFtpdConfigProvider::setServerName(const QString & name)
{
    m_serverName = name;
}

// Network
QString ProFtpdConfigProvider::getServerAddr() const
{
    return m_serverAddr;
}

quint16 ProFtpdConfigProvider::getServerPort() const
{
    return m_parser.get(QLatin1String("Port")).toUInt();
}

void    ProFtpdConfigProvider::setServerPort(quint16 port)
{
    m_parser.set(QLatin1String("Port"), QVariant(port));
}

IServerConfigurationProvider::INTERNET_PROTOCOL::ip ProFtpdConfigProvider::getInternetProtocol() const
{
    bool isIpv6 = m_parser.get(QLatin1String("UseIPv6")).toString() == QLatin1String("on");

    if (isIpv6)
        return IServerConfigurationProvider::INTERNET_PROTOCOL::IPv6;

    return IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4;
}

void ProFtpdConfigProvider::setInternetProtocol(IServerConfigurationProvider::INTERNET_PROTOCOL::ip ip)
{
    if (ip == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv6)
        m_parser.set(QLatin1String("UseIPv6"), QVariant(QLatin1String("on")));
    else if (ip == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4)
        m_parser.set(QLatin1String("UseIPv6"), QVariant(QLatin1String("off")));
}

quint16 ProFtpdConfigProvider::getIdleTimeout() const
{
    return m_parser.get(QLatin1String("TimeoutIdle")).toUInt();
}

void ProFtpdConfigProvider::setIdleTimeout(quint16 timeout)
{
    m_parser.set(QLatin1String("TimeoutIdle"), timeout);
}

quint16 ProFtpdConfigProvider::getDataConnectionTimeout() const
{
    return m_parser.get(QLatin1String("TimeoutStalled")).toUInt();
}

void ProFtpdConfigProvider::setDataConnectionTimeout(quint16 timeout)
{
    m_parser.set(QLatin1String("TimeoutStalled"), timeout);
}

// User
bool ProFtpdConfigProvider::isUsingSystemUser() const
{
    /*if (m_parser.get(QLatin1String("local_enable")).toString() == QLatin1String("YES"))
        return true;
*/
    return false;
}

void ProFtpdConfigProvider::useSystemUser(bool use)
{
    Q_UNUSED(use);
    //m_parser.set(QLatin1String("local_enable"), use ? QLatin1String("YES") : QLatin1String("NO"));
}

bool ProFtpdConfigProvider::isAnonymousAllowed() const
{
    return  m_parser.get(QString("Anonymous /home/ftp#User")) == QString("ftp")
        && m_parser.get(QString("Anonymous /home/ftp#Group")) == QString("nogroup")
        && m_parser.get(QString("Anonymous /home/ftp#UserAlias")) == QString("anonymous ftp")
    ;
}

void ProFtpdConfigProvider::allowAnonymous(bool allow)
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

bool ProFtpdConfigProvider::isAnonymousUploadAllowed() const
{
    return m_parser.get(QString("Anonymous /home/ftp#Directory *#Limit WRITE#DenyAll")).isValid();
}

void ProFtpdConfigProvider::allowAnonymousUpload(bool allow)
{
    if (allow) {
        m_parser.set(QString("Anonymous /home/ftp#Directory *#Limit WRITE#DenyAll"));
    } else {
        m_parser.set(QString("Anonymous /home/ftp#Directory *#Limit WRITE#DenyAll"), QVariant(), false);
    }
}

bool ProFtpdConfigProvider::isAnonymousCreateDirAllowed() const
{
    return isAnonymousUploadAllowed();
}

void ProFtpdConfigProvider::allowAnonymousCreateDir(bool allow)
{
    allowAnonymousUpload(allow);
}

// Virtual User Management
void ProFtpdConfigProvider::setVirtualUserAuthentication(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth mode)
{
    Q_UNUSED(mode);
}

IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth ProFtpdConfigProvider::getVirtualUserAuthentication() const
{
    return IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::Anonymous;
}

void ProFtpdConfigProvider::addVirtualUser(const QString & user, const QString & password)
{
    Q_UNUSED(user);
    Q_UNUSED(password);
  //  m_authentificator->addUser(QLatin1String(user), QLatin1String(password));
}

void ProFtpdConfigProvider::remVirtualUser(const QString & user)
{
    Q_UNUSED(user);
   // m_authentificator->removeUser(QLatin1String(user));
}

QStringList ProFtpdConfigProvider::virtualUsers() const
{
    return QStringList();
}

// Misc
QString ProFtpdConfigProvider::getWelcomeMessage() const
{
    return m_parser.get(QLatin1String("DisplayLogin")).toString();
}

void ProFtpdConfigProvider::setWelcomeMessage(const QString & message)
{
    m_parser.set(QLatin1String("DisplayLogin"), QVariant(message));
}

// Log
QString ProFtpdConfigProvider::getLogFile() const
{
    return m_parser.get(QLatin1String("ServerLog")).toString();
}

// Start/stop
void ProFtpdConfigProvider::start() const
{
    int exitStatus = ServiceManager::start(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
}

void ProFtpdConfigProvider::stop() const
{
    int exitStatus = ServiceManager::stop(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
}

void ProFtpdConfigProvider::restart() const
{
    int exitStatus = ServiceManager::restart(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
 }

QString ProFtpdConfigProvider::exportConfiguration() const
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

void ProFtpdConfigProvider::importConfiguration(const QString & configuration)
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

void ProFtpdConfigProvider::resetConfiguration()
{
}
