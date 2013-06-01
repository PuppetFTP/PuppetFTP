#include <QLibrary>

#include "pluginmanager.h"

/*!
 * \class PluginManager
 * \brief The PluginManager class allows the application to load plugins
 *
 *  The plugin Manager use internaly QLibrary.
 *
 *  Typical usage would be:
 *
 *  QSharedPointer < Plugin > plugin = PluginManager::instance()->loadPlugin(QLatin1String("Proftpd"));
 *  if (plugin.isNull())
 *      qdebug() <<  PluginManager::instance().lastErrorString();
 *  else
 *      ...
 */

PluginManager * PluginManager::m_this = 0;

/*!
 * \fn PluginManager * PluginManager::instance()
 *
 *  Returns an instance of PluginManager
 */
PluginManager * PluginManager::instance()
{
    static QMutex mutex;

    if (!m_this) {
        QMutexLocker locker(&mutex);
        Q_UNUSED (locker);

        if (!m_this)
            m_this = new PluginManager();
    }

    return m_this;
}

/*!
 * \fn QString PluginManager::lastErrorString() const
 *
 *  Returns the last error occured during PluginManager processes.
 *  The lastErrorString if nothings happened.
 */
QString PluginManager::lastErrorString() const
{
    return m_lastError;
}

/*!
 * \fn void PluginManager::setLastError(const QString & errorString)
 *
 * \internal
 */
void PluginManager::setLastError(const QString & errorString)
{
    m_lastError = errorString;
}

/*!
 * QString PluginManager::pluginFileName(const QString & pluginName)
 *
 * \internal
 */
QString PluginManager::pluginFileName(const QString & pluginName)
{
#ifdef Q_OS_WIN
    return QString(QLatin1String(".\\plugins\\%1")).arg(pluginName.toLower());
#else
    return QString(QLatin1String("./plugins/lib%1")).arg(pluginName.toLower());
#endif // Q_OS_WIN
}

typedef Plugin* (* Instance)();

/*!
 * \fn QSharedPointer < Plugin > PluginManager::loadPlugin(const QString & pluginName)
 *
 *  Return a QSharedPointer < Plugin > instance of the /a pluginName requested.
 *
 *  The given \sa pluginName refers to the PuppetFtp Plugin library laying in Library folder.
 *  Loaded Libraries are holded in a cache.
 */
QSharedPointer < Plugin > PluginManager::loadPlugin(const QString & pluginName)
{
    if (!pluginName.isEmpty()) {
        QLibrary lib(pluginFileName(pluginName));
        Instance symbole = (Instance)lib.resolve("instance");
        if (symbole) {
            Plugin * plugin = symbole();
            if (plugin) {
                QString className = plugin->name();
                if (className.toLower() == pluginName.toLower())
                    return QSharedPointer < Plugin >(plugin);

                setLastError(QString(QLatin1String("Invocated plugin %1 not seem to be the expected one: %2"))
                             .arg(className, pluginName));
            }

            setLastError(QString(QLatin1String("Plugin %1 invokation failed")).arg(pluginName));
        } else {
            setLastError(lib.errorString());
        }
    }

    return QSharedPointer < Plugin >();
}

