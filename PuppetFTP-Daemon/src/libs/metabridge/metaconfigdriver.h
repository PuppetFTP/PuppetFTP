#ifndef METABRIDGEDRIVER_H
#define METABRIDGEDRIVER_H

#include <QString>
#include <QVariant>
#include <QStringList>
#include <QCache>
#include <QSharedPointer>

#include "metaconfig.h"
#include "metaplugin.h"

class MetaConfigDriver
{
public:
    MetaConfigDriver();

    bool loadPlugin(const QString & pluginId, const QString & pluginName);
    bool unloadPlugin(const QString & pluginId);

    bool set(const QString & pluginId, const QString & propertyName, const QVariant & value = QVariant());
    QVariant get(const QString & pluginId, const QString & propertyName);

    QVariant exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList = QVariantList());

    QStringList metaProperties(const QString & pluginId);
    QStringList metaTasks(const QString & pluginId);

    QString lastErrorString();
private:
    void setLastErrorString(const QString & errorString);
    MetaConfig * tryToGetMetaConfig(const QString & pluginId);

private:
    QCache < QString, MetaConfig > m_cache;
    QString m_lastError;
};

#endif // METABRIDGEDRIVER_H
