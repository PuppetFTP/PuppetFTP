#ifndef PROFTPD_H
#define PROFTPD_H

#include <iostream>
#include "chrootlist.h"
#include "proftpdconfig.h"
#include "pamauthentication.h"
#include "CommunicationException.h"
#include "serverconfig.h"

#include "plugin.h"

class Proftpd : public Plugin
{
    Q_OBJECT

public:
    Proftpd();
    ~Proftpd();

    // Plugin management
    Q_INVOKABLE void initialize(ServerConfig & config);

    // Communication requirement
    Q_INVOKABLE IServerConfigurationProvider * getServerConfigurationProvider() const;

private:
    IServerConfigurationProvider * m_configurationProvider;
    AbstractAuthentication * m_authentificator;
};

#endif // PROFTPD_H
