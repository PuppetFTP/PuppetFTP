#include "proftpd.h"

Proftpd::Proftpd()
{
    setName(QLatin1String("Proftpd"));
    setGroup(QLatin1String("FTP"));
    initialize(*(ServerConfig::getInstance()));
}

void Proftpd::initialize(ServerConfig & config)
{
    m_serverName = config.get(ServerConfig::serverNameName);
    m_serverAddr = config.get(ServerConfig::serverAddrName);
    m_binPath = config.get(ServerConfig::binPathName);
    m_configFile = config.get(ServerConfig::configFileName);
}

MetaConfig * Proftpd::getMetaConfigInstance()
{
//    return new MetaConfig();
    return new ProFtpdConfigHandler(m_serverName, m_serverAddr, m_configFile, m_binPath);
}

EXPORT_PLUGIN(Proftpd)
