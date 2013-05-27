#ifndef METABRIDGE_H
#define METABRIDGE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QString>
#include <QCache>

#include <QVariantList>

typedef QList < QGenericArgument > ArgumentList;

class MetaBridge : public QObject
{
    Q_OBJECT

public:
    MetaBridge();

    QVariant get(const QString & propertyName);
    bool set(const QString & propertyName, const QVariant & value);
    QVariant exec(const QString & taskName, const QVariantList & argumentList);
    bool is(const QString & ability);

    QStringList metaProperties();
    QStringList metaTasks();
    QStringList metaAbilities();

    QCache < QString, QStringList> m_cache;
};

#endif // METABRIDGE_H
