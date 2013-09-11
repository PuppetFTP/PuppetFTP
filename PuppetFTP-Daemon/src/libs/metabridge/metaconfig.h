#ifndef METABRIDGE_H
#define METABRIDGE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QString>
#include <QCache>

#include <QVariantList>

typedef QList < QGenericArgument > ArgumentList;

class MetaConfig : public QObject
{
    Q_OBJECT

public:
    MetaConfig();

    QVariant get(const QString & propertyName);
    bool set(const QString & propertyName, const QVariant & value);
    QVariant exec(const QString & taskName, const QVariantList & argumentList);

    QStringList metaProperties();
    QStringList metaTasks();

private:
    QCache < QString, QStringList> m_cache;
};

#endif // METABRIDGE_H
