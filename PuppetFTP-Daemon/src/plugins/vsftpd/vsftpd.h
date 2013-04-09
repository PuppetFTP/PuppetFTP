#ifndef VSFTPD_H
#define VSFTPD_H

#include "iabstractplugin.h"
#include "chrootlist.h"
#include "vsftpdconfig.h"
#include "vsftpdparser.h"
#include "pamauthentication.h"
#include "CommunicationException.h"

class Vsftpd : public QObject, public IAbstractPlugin
{
    Q_OBJECT
    Q_INTERFACES(IAbstractPlugin)
public:
    Vsftpd();
    ~Vsftpd();

    // Plugin management
    void                            initialize(ServerConfig & config);

    // Communication requirement
    IServerConfigurationProvider    * getServerConfigurationProvider() const;

private:
    VsftpdParser m_parser;
    IServerConfigurationProvider    * m_configurationProvider;
    AbstractAuthentication          * m_authentificator;
};

#endif // VSFTPD_H
