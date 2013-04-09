#ifndef IABSTRACTPLUGIN_H
#define IABSTRACTPLUGIN_H

#include <QtPlugin>
#include "IServerConfigurationProvider.h"
#include "ipluginprovider.h"

class IAbstractPlugin
{
public:
    virtual ~IAbstractPlugin()  {}

    // Plugin management
    virtual void                            initialize(ServerConfig & config)            = 0;

    // ServerConfigurationProvider
    virtual IServerConfigurationProvider    *getServerConfigurationProvider()      const = 0;

};
Q_DECLARE_INTERFACE(IAbstractPlugin, "com.puppetFTP.IAbstractPlugin")

#endif // IABSTRACTPLUGIN_H
