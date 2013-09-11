#ifndef METABRIDGEDRIVER_H
#define METABRIDGEDRIVER_H

#include <QString>
#include <QVariant>
#include <QStringList>
#include <QCache>

#include "metaconfig.h"
#include "metaplugin.h"
#include "lasterror.h"
#include "IServerConfigurationProvider.h"

class MetaConfigDriver : public LastError, public IServerConfigurationProvider
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
    bool hasFailure();

private:
    MetaConfig * tryToGetMetaConfig(const QString & pluginId);

private:
    QCache < QString, MetaConfig > m_cache;
};

#endif // METABRIDGEDRIVER_H
