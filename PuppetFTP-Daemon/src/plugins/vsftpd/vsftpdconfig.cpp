#include <QtPlugin>
#include <QSettings>
#include <QDir>
#include <QProcess>

#include "vsftpdconfig.h"

VsftpdConfigHandler::VsftpdConfigHandler(const QString & serverName, const QString & serverAddr, const QString & fileName, const QString & serverBinPath)
    : m_parser(fileName), m_serverName(serverName), m_serverAddr(serverAddr), m_serverPath(serverBinPath), m_serviceName("vsftpd")
{
}

VsftpdConfigHandler::~VsftpdConfigHandler()
{
}

QString VsftpdConfigHandler::getServerName() const
{
    return m_serverName;
}

void    VsftpdConfigHandler::setServerName(const QString & name)
{
    m_serverName = name;
}

// Network
QString VsftpdConfigHandler::getServerAddr() const
{
    return m_serverAddr;
}

quint16 VsftpdConfigHandler::getServerPort()
{
    bool convert;
    quint16 port = m_parser.get(QLatin1String("listen_port")).toUInt(&convert);
    if (convert)
        return port;

    return 21;
}

void    VsftpdConfigHandler::setServerPort(quint16 port)
{
    m_parser.set(QLatin1String("listen_port"), QVariant(port));
}

QString VsftpdConfigHandler::getInternetProtocol()
{
    QString ipv4 = m_parser.get(QLatin1String("listen")).toString();
    QString ipv6 = m_parser.get(QLatin1String("listen_ipv6")).toString();

    if (ipv6 == QLatin1String("YES") && ipv4 != QLatin1String("YES"))
        return QLatin1String("IPv6");

    if (ipv4 == QLatin1String("YES") && ipv6 != QLatin1String("YES"))
        return QLatin1String("IPv4");

    return QLatin1String("undefined");
}

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

quint16 VsftpdConfigHandler::getIdleTimeout()
{
    return m_parser.get(QLatin1String("idle_session_timeout")).toUInt();
}

void VsftpdConfigHandler::setIdleTimeout(quint16 to)
{
    m_parser.set(QLatin1String("idle_session_timeout"), to);
}

quint16 VsftpdConfigHandler::getDataConnectionTimeout()
{
    return m_parser.get(QLatin1String("data_connection_timeout")).toUInt();
}

void VsftpdConfigHandler::setDataConnectionTimeout(quint16 to)
{
    m_parser.set(QLatin1String("data_connection_timeout"), to);
}

// Anonymous User
bool VsftpdConfigHandler::isAnonymousEnabled()
{
    return m_parser.get(QLatin1String("anonymous_enable")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::enableAnonymous(bool allow)
{
    m_parser.set(QLatin1String("anonymous_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

QString VsftpdConfigHandler::anonymousRoot()
{
    return (m_parser.get(QLatin1String("anon_root")).toString());
}

void VsftpdConfigHandler::setAnonymousRoot(const QString & anonymousRoot)
{
    m_parser.set(QLatin1String("anon_root"), anonymousRoot);
}

bool VsftpdConfigHandler::isAnonymousUploadEnabled()
{
    return m_parser.get(QLatin1String("anon_upload_enable")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::enableAnonymousUpload(bool allow)
{
    m_parser.set(QLatin1String("anon_upload_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isWriteEnabled()
{
    return m_parser.get(QLatin1String("write_enable")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::enableWrite(bool allow)
{
    m_parser.set(QLatin1String("write_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isAnonymousWorldReadable()
{
    return m_parser.get(QLatin1String("anon_world_readeable")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::allowAnonymousWorldReadable(bool allow)
{
    m_parser.set(QLatin1String("anon_world_readeable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isAnonOtherWriteEnable()
{
    return m_parser.get(QLatin1String("anon_other_write_enable")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::enableAnonOtherWrite(bool allow)
{
    m_parser.set(QLatin1String("anon_other_write_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isAnonymousMakeDirAllowed()
{
    return m_parser.get(QLatin1String("anon_mkdir_write_enable")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::allowAnonymousMakeDir(bool allow)
{
    m_parser.set(QLatin1String("anon_mkdir_write_enable"), allow ? QLatin1String("YES") : QLatin1String("NO"));
}

// Regular User
bool VsftpdConfigHandler::isUsingSystemUser()
{
    return m_parser.get(QLatin1String("local_enable")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::useSystemUser(bool use)
{
    m_parser.set(QLatin1String("local_enable"), use ? QLatin1String("YES") : QLatin1String("NO"));
}

bool VsftpdConfigHandler::isChrootLocalUser()
{
    return m_parser.get(QLatin1String("chroot_local_user")).toString() == QLatin1String("YES");
}

void VsftpdConfigHandler::chrootLocalUser(bool use)
{
    m_parser.set(QLatin1String("chroot_local_user"), use ? QLatin1String("YES") : QLatin1String("NO"));
}

// Misc
QString VsftpdConfigHandler::getWelcomeMessage()
{
    return m_parser.get(QLatin1String("ftpd_banner")).toString();
}

void VsftpdConfigHandler::setWelcomeMessage(const QString & msg)
{
    m_parser.set(QLatin1String("ftpd_banner"), (msg));
}

// Log
QString VsftpdConfigHandler::getLogFile()
{
    return m_parser.get(QLatin1String("xferlog_file")).toString();
}

// Start/stop
void VsftpdConfigHandler::start()
{
    ServiceManager::start(m_serviceName);
}

void VsftpdConfigHandler::stop()
{
    ServiceManager::stop(m_serviceName);
}

void VsftpdConfigHandler::restart()
{
    ServiceManager::restart(m_serviceName);
}

QString VsftpdConfigHandler::parserFileName() const
{
    return m_parser.fileName();
}

void VsftpdConfigHandler::setParserFileName(const QString & filename)
{
    m_parser.setFileName(filename);
}

bool VsftpdConfigHandler::isParserDryRun() const
{
    return m_parser.isDryRun();
}

void VsftpdConfigHandler::setParserDryRun(bool dryRun)
{
    m_parser.setDryRun(dryRun);
}

QString VsftpdConfigHandler::parserData()
{
    return m_parser.Data();
}

void VsftpdConfigHandler::setParserData(const QString & data)
{
    m_parser.setData(data);
}

QString VsftpdConfigHandler::parserLastError()
{
    return m_parser.lastError();
}
