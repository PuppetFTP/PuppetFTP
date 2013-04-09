/*
 * Table.h
 *
 *  Created on: 13 nov. 2012
 *      Author: Vince
 */

#ifndef Table_H
#define Table_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QMetaProperty>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlField>
#include "DatabaseManager.h"
#include "ITable.h"
#include "Query.h"

template<class E>
class Table : public ITable {
protected:
      QList<QMetaProperty>    _properties;

public:
    Table() {
        for (int i = 0; i < E::staticMetaObject.propertyCount(); i++) {
            QString tmp = E::staticMetaObject.property(i).name();
            if (tmp != "objectName") {
                _properties << E::staticMetaObject.property(i);
            }
        }
    }

    virtual ~Table() {}

//    virtual QString getName() const = 0;
//    virtual QStringList getPrimaryKeys() const = 0;

    QList<QObject*> getAll() const {
        Query q;
        q.select()->from(getName());
        return rawToObjects(DatabaseManager::instance()->performQuery(q));
    }

    bool save(QObject* element) const {
        bool updateInsteadOfInsert = true;
        QStringList pks = getPrimaryKeys();
        const QMetaObject* meta = element->metaObject();
        QString field;
        foreach (field, pks)
            if (meta->property(meta->indexOfProperty(field.toStdString().c_str())).read(element) == 0)
                updateInsteadOfInsert = false;
        bool res = false;
        if (updateInsteadOfInsert) {
            QMap<QString, QVariant> values, where;
            foreach (field, getFields()) {
                if (pks.contains(field))
                    where[field] = meta->property(meta->indexOfProperty(field.toStdString().c_str())).read(element);
                else
                    values[field] = meta->property(meta->indexOfProperty(field.toStdString().c_str())).read(element);
            }
            Query q;
            q.update(values)->into(getName())->where(where);
            QSqlQuery result = DatabaseManager::instance()->performQuery(q);
            res = result.lastError().isValid() == false;
        }
        else {
            QMap<QString, QVariant> values;
            foreach (field, getFields())
                if (!pks.contains(field))
                    values[field] = meta->property(meta->indexOfProperty(field.toStdString().c_str())).read(element);
            Query q;
            q.insert(values)->into(getName());
            QSqlQuery result = DatabaseManager::instance()->performQuery(q);
            res = result.lastError().isValid() == false;
        }
        return res;
    }

    bool remove(QObject* element) const {
        Query q;
        QMap<QString, QVariant> where;
        const QMetaObject* meta = element->metaObject();
        QString field;
        foreach (field, getPrimaryKeys())
            where[field] = meta->property(meta->indexOfProperty(field.toStdString().c_str())).read(element);
        q.remove()->from(getName())->where(where);
        QSqlQuery result = DatabaseManager::instance()->performQuery(q);
        return result.lastError().isValid() == false;
    }

    QList<QObject*> find(const QMap<QString, QVariant>& where) const {
        Query q;
        q.select()->from(getName())->where(where);
        return rawToObjects(DatabaseManager::instance()->performQuery(q));
    }

    QList<QObject*> find(const QString& field, const QVariant& value) const {
        Query q;
        q.select()->from(getName())->where(field, value);
        return rawToObjects(DatabaseManager::instance()->performQuery(q));
    }

    QObject* get(const QMap<QString, QVariant>& where) const {
        QList<QObject*> res = find(where);
        return res.isEmpty() || res.at(0) == 0 ? 0 : res.at(0);
    }

    QObject* get(const QString& field, const QVariant& value) const {
        QList<QObject*> res = find(field, value);
        return res.isEmpty() || res.at(0) == 0 ? 0 : res.at(0);
    }

private:
    QStringList getFields() const {
        QStringList fields;
        for (QList<QMetaProperty>::const_iterator it = _properties.begin(); it != _properties.end(); it++) {
            fields << it->name();
        }
        return fields;
    }

    QList<QObject*>   rawToObjects(QSqlQuery table) const {
        QList<QObject*> result = QList<QObject*>();
        QStringList fields = getFields();
        table.first();
        while (table.isValid()) {
            QSqlRecord row = table.record();
            E* element = new E();
            const QMetaObject* meta = (dynamic_cast<QObject*>(element))->metaObject();
            QString field;
            foreach (field, fields)
                meta->property(meta->indexOfProperty(field.toStdString().c_str())).write(element, row.field(field).value());
            result.append(dynamic_cast<QObject*>(element));
            table.next();
        }
        return result;
    }
};

#endif // Table_H
