#ifndef ABSTRACTPLUGIN_H
#define ABSTRACTPLUGIN_H

#include <QtPlugin>
#include "iabstractplugin.h"

class AbstractPlugin
{
public:
    static IAbstractPlugin  *load(ServerConfig & config);
};

#endif // ABSTRACTPLUGIN_H
