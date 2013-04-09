/*
 * ITable.h
 *
 *  Created on: 13 nov. 2012
 *      Author: Vince
 */

#ifndef ITABLE_H
#define ITABLE_H

#include <QString>
#include <QObject>

class ITable {
public:
    virtual ~ITable() {}
    virtual QString getName() const = 0;
    virtual QStringList getPrimaryKeys() const = 0;
    virtual QList<QObject*> getAll() const = 0;
    virtual bool save(QObject* element) const = 0;
    virtual bool remove(QObject* element) const = 0;
    virtual QList<QObject*> find(const QMap<QString, QVariant>& where) const = 0;
    virtual QList<QObject*> find(const QString& field, const QVariant& value) const = 0;
    virtual QObject* get(const QMap<QString, QVariant>& where) const = 0;
    virtual QObject* get(const QString& field, const QVariant& value) const = 0;
};

#endif // ITABLE_H
