#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QSharedPointer>
#include <QMutex>

#include "plugin.h"

class PluginManager
{
public:
    static PluginManager * instance();

    QString pluginFileName(const QString & pluginName);
    QSharedPointer < Plugin > loadPlugin(const QString & pluginName);

    QString lastErrorString() const;

protected:
    void setLastError(const QString & errorString);

private:
    static PluginManager * m_this;
    QString m_lastError;

};

#endif // PLUGINMANAGER_H
