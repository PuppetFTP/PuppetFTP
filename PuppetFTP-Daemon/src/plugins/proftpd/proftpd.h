#ifndef PROFTPD_H
#define PROFTPD_H

#include <iostream>
#include "iabstractplugin.h"
#include "chrootlist.h"
#include "proftpdconfig.h"
#include "pamauthentication.h"
#include "CommunicationException.h"

class Proftpd : public QObject, public IAbstractPlugin
{
    Q_OBJECT
    Q_INTERFACES(IAbstractPlugin)
public:
    Proftpd();
    ~Proftpd();

    // Plugin management
    void                            initialize(ServerConfig & config);

    // Communication requirement
    IServerConfigurationProvider    * getServerConfigurationProvider() const;

private:
    ProftpdParser                   m_parser;
    IServerConfigurationProvider    * m_configurationProvider;
    AbstractAuthentication          * m_authentificator;
};

#endif // PROFTPD_H
