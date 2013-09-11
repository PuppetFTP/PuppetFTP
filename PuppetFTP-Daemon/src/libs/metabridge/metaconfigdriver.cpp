#include "metaconfigdriver.h"
#include "pluginmanager.h"

/*!
    \class MetaConfigDriver
    \brief The MetaConfigDriver is the main element of the meta system.
    It's provide a way to load metaPlugins and retrieve MetaConfig instance and then to drive them
 */

MetaConfigDriver::MetaConfigDriver()
{
    setLastErrorString("HUSS");
}

/*!
    \fn bool MetaConfigDriver::loadPlugin(const QString & pluginId, const QString & pluginName)

    Loads the given \a pluginName Metaplugin and hold the MetaConfig object as a reference of the \a pluginId

    Return true on success else a lastError is set
 */
bool MetaConfigDriver::loadPlugin(const QString & pluginId, const QString & pluginName)
{
    if (!m_cache.contains(pluginId)) {
        QSharedPointer < Plugin > plugin = PluginManager::instance()->loadPlugin(pluginName);
        if (!plugin.isNull()) {
            if (plugin->type() == QLatin1String(META_PLUGIN)) {
                QSharedPointer < MetaPlugin > metaPlugin = plugin.staticCast < MetaPlugin > ();
                if (!metaPlugin.isNull()) {
                    MetaConfig * metaConfigObject = metaPlugin->getMetaConfigInstance();
                    if (metaConfigObject) {
                        m_cache.insert(pluginId, metaConfigObject);
                        return true;
                    } else {
                        setLastErrorString(QString(QLatin1String("This pluginId doesn'o't provide MetaConfig: %1")).arg(pluginId));
                    }
                } else {
                    setLastErrorString(QLatin1String("unable to load MetaPlugin"));
                }
            } else {
                setLastErrorString(QLatin1String("This is not a metaPlugin"));
            }
        } else {
            setLastErrorString(PluginManager::instance()->lastErrorString());
        }
    } else {
        setLastErrorString(QString(QLatin1String("This pluginId is already loaded: %1")).arg(pluginId));
    }

    return false;
}

/*!
    \fn bool MetaConfigDriver::unloadPlugin(const QString & pluginId)

    Unload the MetaConfig object referenced as \a pluginId
 */
bool MetaConfigDriver::unloadPlugin(const QString & pluginId)
{
    return m_cache.remove(pluginId);
}

/*!
    \fn bool MetaConfigDriver::set(const QString & pluginId, const QString & propertyName, const QVariant & value)
    Set the \a propertyName of the referenced plugin \a pluginId with given \a value

    Return true if succesfull
 */
bool MetaConfigDriver::set(const QString & pluginId, const QString & propertyName, const QVariant & value)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->set(propertyName, value);

    return false;
}

/*!
    \fn QVariant MetaConfigDriver::get(const QString & pluginId, const QString & propertyName)
    Get the \a propertyName of the referenced plugin \a pluginId

    Return the value as a QVariant
 */
QVariant MetaConfigDriver::get(const QString & pluginId, const QString & propertyName)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->get(propertyName);

    return QVariant();
}

/*!
    \fn QVariant MetaConfigDriver::exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList)
    Execute the \a taskName of the referenced \a pluginId with the given \a argumentList

    Return the result of the task as a QVariant
 */
QVariant MetaConfigDriver::exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->exec(taskName, argumentList);

    return QVariant();
}

/*!
    \fn QStringList MetaConfigDriver::metaProperties(const QString & pluginId)

    Retrieves the metaProperties list of the referenced \a pluginId
 */
QStringList MetaConfigDriver::metaProperties(const QString & pluginId)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->metaProperties();

    return QStringList();
}

/*!
    \fn QStringList MetaConfigDriver::metaTasks(const QString & pluginId)

    Retrieves the metaTasks list of the referenced \a pluginId
 */
QStringList MetaConfigDriver::metaTasks(const QString & pluginId)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->metaTasks();

    return QStringList();
}

/*!
    \fn MetaConfig * MetaConfigDriver::tryToGetMetaConfig(const QString & pluginId)

    Try to retrieve the plugin referenced as \a pluginId from the cache

    \internal
 */
MetaConfig * MetaConfigDriver::tryToGetMetaConfig(const QString & pluginId)
{
    MetaConfig * metaConfig = m_cache.object(pluginId);
    if (metaConfig)
        return metaConfig;

    setLastErrorString(QString(QLatin1String("This pluginId is not loaded: %1")).arg(pluginId));

    return NULL;
}

QString MetaConfigDriver::lastErrorString()
{
    return LastError::lastError();
}

bool MetaConfigDriver::hasFailure()
{
    return LastError::hasFailure();
}
