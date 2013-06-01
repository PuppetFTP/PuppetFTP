#include <QtPlugin>
#include <QSettings>
#include <QDir>
#include <QProcess>
#include <iostream>

#include "vsftpdconfig.h"
#include "chrootlist.h"
#include "pamauthentication.h"

#include "CommunicationException.h"

VsftpdConfigHandler::VsftpdConfigHandler(QString serverName, QString serverAddr, QString fileName, QString serverBinPath)
    : m_serverName(serverName), m_serverAddr(serverAddr), m_parser(fileName), m_serverPath(serverBinPath),  m_serviceName("vsftpd")
{
}

VsftpdConfigHandler::~VsftpdConfigHandler()
{
}

/********************************************************************************/

QString VsftpdConfigHandler::getServerName() const
{
    return (m_serverName);
}

void    VsftpdConfigHandler::setServerName(const QString & name)
{
    m_serverName = name;
}

// Network
QString VsftpdConfigHandler::getServerAddr() const
{
    return (m_serverAddr);
}

quint16 VsftpdConfigHandler::getServerPort() const
{
    bool convert;
    qint64 port = m_parser.get(QLatin1String("listen_port")).toDouble(&convert);
    if (convert)
        return port;
    return 21;
}

void    VsftpdConfigHandler::setServerPort(quint16 port)
{
    m_parser.set(QLatin1String("listen_port"), QVariant(port));
}

QString VsftpdConfigHandler::getInternetProtocol() const
{
    QString ipv4 = m_parser.get(QLatin1String("listen")).toString();
    QString ipv6 = m_parser.get(QLatin1String("listen_ipv6")).toString();

    if (ipv6 == QLatin1String("YES") && ipv4 != QLatin1String("YES"))
        return QLatin1String("IPv6");

    if (ipv4 == QLatin1String("YES") && ipv6 != QLatin1String("YES"))
        return QLatin1String("IPv4");

    return QLatin1String("undefined");
}

// need etre root ?
void VsftpdConfigHandler::setInternetProtocol(const QString & ip)
{
    if (ip == QLatin1String("IPv6")) {
        m_parser.set(QLatin1String("listen_ipv6"), QVariant(QLatin1String("YES")));
        m_parser.set(QLatin1String("listen"), QVariant(QLatin1String("NO")));
    } else if (ip == QLatin1String("IPv4")) {
        m_parser.set(QLatin1String("listen"), QVariant(QLatin1String("YES")));
        m_parser.set(QLatin1String("listen_ipv6"), QVariant(QLatin1String("NO")));
    }
}

quint16 VsftpdConfigHandler::getIdleTimeout() const
{
    return m_parser.get(QLatin1String("idle_session_timeout")).toUInt();
}

void VsftpdConfigHandler::setIdleTimeout(quint16 to)
{
    m_parser.set(QLatin1String("idle_session_timeout"), to);
}

quint16 VsftpdConfigHandler::getDataConnectionTimeout() const
{
    return m_parser.get(QLatin1String("data_connection_timeout")).toUInt();
}

void VsftpdConfigHandler::setDataConnectionTimeout(quint16 to)
{
    m_parser.set(QLatin1String("data_connection_timeout"), to);
}

// User
/*
bool VsftpdConfigHandler::isUsingSystemUser() const
{
    if (m_parser.get(QLatin1String("local_enable")).toString() == QLatin1String("YES"))
        return true;

    return false;
}

void VsftpdConfigHandler::useSystemUser(bool use)
{
    qDebug() << use;
    m_parser.set(QLatin1String("local_enable"), use ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isAnonymousAllowed() const
{
    if (m_parser.get(QLatin1String("anonymous_enable")).toString() == QLatin1String("YES"))
        return true;

    return false;
}

void VsftpdConfigHandler::allowAnonymous(bool allow)
{
    m_parser.set(QLatin1String("anonymous_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isAnonymousUploadAllowed() const
{
    if (m_parser.get(QLatin1String("anon_upload_enable")).toString() == QLatin1String("YES"))
        return true;

    return false;
}

void VsftpdConfigHandler::allowAnonymousUpload(bool allow)
{
    if (allow)
        m_parser.set(QLatin1String("write_enable"), QLatin1String("YES"));

    m_parser.set(QLatin1String("anon_upload_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isAnonymousCreateDirAllowed() const
{
    if (m_parser.get(QLatin1String("anon_mkdir_write_enable")).toString() == QLatin1String("YES")
        && m_parser.get(QLatin1String("write_enable")).toString() == QLatin1String("YES"))
        return true;

    return false;
}

void VsftpdConfigHandler::allowAnonymousCreateDir(bool allow)
{
    m_parser.set(QLatin1String("anon_mkdir_write_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

// Virtual User Management
void VsftpdConfigHandler::setVirtualUserAuthentication(::IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth mode)
{
    if (mode == IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::Anonymous) {
    // Configure for authentication
        const QString & chrootPath = QLatin1String("/etc/vsftpd/vsftpd.chroot_list");
        /*
          We should also do some setup:
        m_parser.set(QLatin1String("listen"), QLatin1String("YES"));
        m_parser.set(QLatin1String("anonymous_enable"), QLatin1String("YES"));

        m_parser.set(QLatin1String("local_enable"), QLatin1String("YES"));
        m_parser.set(QLatin1String("write_enable"), QLatin1String("YES"));
        */
     /*   m_parser.set(QLatin1String("chroot_list_file"), chrootPath);
        m_parser.set(QLatin1String("chroot_list_enable"), QLatin1String("YES"));
        m_parser.set(QLatin1String("chroot_local_user"), QLatin1String("NO"));

        m_authentificator = new ChrootList(chrootPath);
    }
}

IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth VsftpdConfigHandler::getVirtualUserAuthentication() const
{
    return IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::Anonymous;
}

void VsftpdConfigHandler::addVirtualUser(const QString & user, const QString & password)
{
    m_authentificator->addUser(user, password);
}

void VsftpdConfigHandler::remVirtualUser(const QString & user)
{
    m_authentificator->removeUser((user));
}

QStringList VsftpdConfigHandler::virtualUsers() const
{
    return QStringList();
}
*/
// Misc
QString VsftpdConfigHandler::getWelcomeMessage() const
{
    return (m_parser.get(QLatin1String("ftpd_banner")).toString());
}

void VsftpdConfigHandler::setWelcomeMessage(const QString & msg)
{
    m_parser.set(QLatin1String("ftpd_banner"), (msg));
}

// Log
QString VsftpdConfigHandler::getLogFile() const
{
    return (m_parser.get(QLatin1String("xferlog_file")).toString());
}

// Start/stop
void VsftpdConfigHandler::start() const
{
    int exitStatus = ServiceManager::start(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
}

void VsftpdConfigHandler::stop() const
{
    int exitStatus = ServiceManager::stop(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
}

void VsftpdConfigHandler::restart() const
{
    int exitStatus = ServiceManager::restart(m_serviceName);
    if (exitStatus == 1) {
        std::string err("The process crashed.");
        throw CommunicationException(err.c_str());
    }
 }

/*
QString VsftpdConfigHandler::exportConfiguration() const
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

void VsftpdConfigHandler::importConfiguration(const QString & configuration)
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

void VsftpdConfigHandler::resetConfiguration()
{
}
*/
