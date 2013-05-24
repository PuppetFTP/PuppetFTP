#ifndef VSFTPD_H
#define VSFTPD_H

#include "iabstractplugin.h"
#include "chrootlist.h"
#include "vsftpdconfig.h"
#include "vsftpdparser.h"
#include "pamauthentication.h"
#include "CommunicationException.h"

#include "plugin.h"

class Vsftpd : public Plugin
{
public:
    Vsftpd();
    ~Vsftpd();

    // Plugin management
    Q_INVOKABLE void initialize(ServerConfig & config);

    // Communication requirement
    Q_INVOKABLE IServerConfigurationProvider * getServerConfigurationProvider() const;

private:
    IServerConfigurationProvider * m_configurationProvider;
    AbstractAuthentication * m_authentificator;
};

#endif // VSFTPD_H
