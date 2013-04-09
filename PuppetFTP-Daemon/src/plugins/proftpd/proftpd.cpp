#include "proftpd.h"

Proftpd::Proftpd()
    : m_configurationProvider(NULL), m_authentificator(NULL)
{
}

Proftpd::~Proftpd()
{
}

/********************************************************************************/

void Proftpd::initialize(ServerConfig & config)
{
    QString         configFile;
    QString         binPath;
    QString         serverName;
    QString         serverAddr;

    serverName = config.get(ServerConfig::serverNameName);
    serverAddr = config.get(ServerConfig::serverAddrName);
    binPath = config.get(ServerConfig::binPathName);
    configFile = config.get(ServerConfig::configFileName);
    m_configurationProvider = new ProFtpdConfigProvider(serverName, serverAddr, configFile, binPath);
}

IServerConfigurationProvider    *Proftpd::getServerConfigurationProvider() const
{
    return m_configurationProvider;
}

Q_EXPORT_PLUGIN2(proftpd_plugin, Proftpd)
