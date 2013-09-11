#ifndef VSFTPD_H
#define VSFTPD_H

#include "chrootlist.h"
#include "vsftpdconfig.h"
#include "vsftpdparser.h"
#include "pamauthentication.h"
#include "CommunicationException.h"
#include "serverconfig.h"
#include "metaplugin.h"

class Vsftpd : public MetaPlugin
{
public:
    Vsftpd();
    ~Vsftpd();

    // Plugin default config loading from file deprecated soon !
    Q_INVOKABLE void initialize(ServerConfig & config);

    MetaConfig * getMetaConfigInstance();

private:
    // Dependency ingections deprecated Soon !
    QString         m_configFile;
    QString         m_binPath;
    QString         m_serverName;
    QString         m_serverAddr;};

#endif // VSFTPD_H
