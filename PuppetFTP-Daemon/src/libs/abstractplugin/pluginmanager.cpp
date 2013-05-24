#include <QLibrary>

#include "pluginmanager.h"

#include <QDebug>

PluginManager * PluginManager::m_this = 0;

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

QString PluginManager::lastErrorString() const
{
    return m_lastError;
}

void PluginManager::setLastError(const QString & errorString)
{
    m_lastError = errorString;
}

QString PluginManager::pluginFileName(const QString & pluginName)
{
#ifdef Q_OS_WIN
    return QString(QLatin1String(".\\plugins\\%1.dll")).arg(pluginName.toLower());
#else
    return QString(QLatin1String("./plugins/%1.so")).arg(pluginName.toLower());
#endif // Q_OS_WIN
}

typedef Plugin * (* Instance)();

QSharedPointer < Plugin > PluginManager::loadPlugin(const QString & pluginName)
{
    QLibrary lib;
    lib.setFileName(pluginName);
    Instance symbole = (Instance)lib.resolve("instance");

    if (symbole == NULL) {
        Plugin * plugin = symbole();
        if (plugin != NULL) {
            const QString & className = QString::fromUtf8(plugin->metaObject()->className()).toLower();
            if (className != pluginName.toLower()) {
                if (className == QLatin1String("Plugin") || className == QLatin1String("MetaPlugin"))
                    setLastError(QString(QLatin1String("Invocated plugin %1 not seem to use Q_OBJECT"))
                                 .arg(pluginName));
                else
                    setLastError(QString(QLatin1String("Invocated plugin %1 not seem to be the expected one: %2"))
                                 .arg(plugin->metaObject()->className(), pluginName));
            }

            return QSharedPointer < Plugin >(plugin);
        }

        setLastError(QString(QLatin1String("Plugin %1 invokation failed")).arg(pluginName));
    } else {
        setLastError(lib.errorString());
    }

    return QSharedPointer < Plugin >();
}

