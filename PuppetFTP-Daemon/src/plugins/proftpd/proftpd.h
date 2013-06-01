#ifndef PROFTPD_H
#define PROFTPD_H

#include "proftpdconfig.h"
#include "serverconfig.h"
#include "metaplugin.h"

class Proftpd : public MetaPlugin
{
    Q_OBJECT

public:
    Proftpd();

    // Plugin default config loading from file deprecated soon !
    void initialize(ServerConfig & config);

    MetaConfig * getMetaConfigInstance();

private:
    // Deprecated Soon !
    QString         m_configFile;
    QString         m_binPath;
    QString         m_serverName;
    QString         m_serverAddr;

};

#endif // PROFTPD_H
