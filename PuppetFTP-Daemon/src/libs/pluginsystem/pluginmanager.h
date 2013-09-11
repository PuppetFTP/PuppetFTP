#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QSharedPointer>
#include <QMutex>

#include "plugin.h"

class PluginManager
{
    // Manque un contructeur par defau en privé !!!!!!!!!!!!!!!
public:
    static PluginManager * instance();
    QSharedPointer < Plugin > loadPlugin(const QString & pluginName);
    QString lastErrorString() const;

private:
    QString pluginFileName(const QString & pluginName);

protected:
    void setLastError(const QString & errorString);

private:
    static PluginManager * m_this;
    QString m_lastError;

};

#endif // PLUGINMANAGER_H
