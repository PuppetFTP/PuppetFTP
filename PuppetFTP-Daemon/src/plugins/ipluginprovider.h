#ifndef IPLUGINPROVIDER_H
#define IPLUGINPROVIDER_H

#include "serverconfig.h"

class   IPluginProvider
{
public:
    virtual ~IPluginProvider()  {}

    virtual void    initialize(ServerConfig & config)   = 0;
};

#endif // IPLUGINPROVIDER_H
