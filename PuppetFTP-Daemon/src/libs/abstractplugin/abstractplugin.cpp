#include "abstractplugin.h"
#include "abstractpluginexception.h"

IAbstractPlugin     *AbstractPlugin::load(ServerConfig &config)
{
    QPluginLoader                   loader(config.get(ServerConfig::pluginPathName));
    IAbstractPlugin                 *instance;

    instance = qobject_cast<IAbstractPlugin *>(loader.instance());
    if (instance != NULL)
        instance->initialize(config);
    else if (loader.isLoaded())
        throw AbstractPluginException(AbstractPluginException::InvalidCast, config.get(ServerConfig::pluginPathName));
    else
        throw AbstractPluginException(AbstractPluginException::NoPluginAvailable, loader.errorString());//config.get(ServerConfig::pluginPathName));
    return instance;
}
