#include "vsftpd.h"

Vsftpd::Vsftpd()
{
}

Vsftpd::~Vsftpd()
{
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

Q_EXPORT_PLUGIN2(vsftpd, Vsftpd)
