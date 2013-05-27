#include "vsftpd.h"

Vsftpd::Vsftpd()
{
    setName(QLatin1String("Proftpd"));
    setType(QLatin1String("MetaPlugin"));
    setGroup(QLatin1String("FTP"));
}

Vsftpd::~Vsftpd()
{
    if (m_configurationProvider != 0)
        delete m_configurationProvider;

    if (m_authentificator != 0)
        delete m_authentificator;
}

void Vsftpd::initialize(ServerConfig & config)
{
    QString         configFile;
    QString         binPath;
    QString         serverName;
    QString         serverAddr;

    serverName = config.get(ServerConfig::serverNameName);
    serverAddr = config.get(ServerConfig::serverAddrName);
    binPath = config.get(ServerConfig::binPathName);
    configFile = config.get(ServerConfig::configFileName);
    m_configurationProvider = new VsftpdConfigHandler(serverName, serverAddr, configFile, binPath);
}

IServerConfigurationProvider    *Vsftpd::getServerConfigurationProvider() const
{
    return m_configurationProvider;
}

EXPORT_PLUGIN(Vsftpd)
