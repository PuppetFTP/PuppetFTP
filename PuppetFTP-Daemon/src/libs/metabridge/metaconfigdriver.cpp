#include "metaconfigdriver.h"
#include "pluginmanager.h"

MetaConfigDriver::MetaConfigDriver()
{
}

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
                        m_lastError = QString(QLatin1String("This pluginId doesn'o't provide MetaConfig: %1")).arg(pluginId);
                    }
                } else {
                    m_lastError = QLatin1String("unable to load MetaPlugin");
                }
            } else {
                m_lastError = QLatin1String("This is not a metaPlugin");
            }
        } else {
            m_lastError = PluginManager::instance()->lastErrorString();
        }
    } else {
        m_lastError = QString(QLatin1String("This pluginId is already loaded: %1")).arg(pluginId);
    }

    return false;
}

bool MetaConfigDriver::unloadPlugin(const QString & pluginId)
{
    return m_cache.remove(pluginId);
}

bool MetaConfigDriver::set(const QString & pluginId, const QString & propertyName, const QVariant & value)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->set(propertyName, value);

    return false;
}

QVariant MetaConfigDriver::get(const QString & pluginId, const QString & propertyName)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->get(propertyName);

    return QVariant();
}

QVariant MetaConfigDriver::exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->exec(taskName, argumentList);

    return QVariant();
}

QStringList MetaConfigDriver::metaProperties(const QString & pluginId)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->metaProperties();

    return QStringList();
}

QStringList MetaConfigDriver::metaTasks(const QString & pluginId)
{
    MetaConfig * metaConfig = tryToGetMetaConfig(pluginId);
    if (metaConfig)
        return metaConfig->metaTasks();

    return QStringList();
}

QString MetaConfigDriver::lastErrorString()
{
    QString lastError = m_lastError;
    m_lastError.clear();
    return lastError;
}

void MetaConfigDriver::setLastErrorString(const QString & errorString)
{
    m_lastError = errorString;
}

MetaConfig * MetaConfigDriver::tryToGetMetaConfig(const QString & pluginId)
{
    MetaConfig * metaConfig = m_cache.object(pluginId);
    if (metaConfig)
        return metaConfig;

    m_lastError = QString(QLatin1String("This pluginId is not loaded: %1")).arg(pluginId);

    return NULL;
}
