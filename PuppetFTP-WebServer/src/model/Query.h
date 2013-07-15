/*
 * Query.h
 *
 *  Created on: 13 nov. 2012
 *      Author: Vince
 */

#ifndef QUERY_H
#define QUERY_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>

class Query {
protected:

    enum QueryType {
        SELECT,
        INSERT,
        UPDATE,
        REMOVE
    };

    QueryType                                   _type;
    QMap<QString, QVariant>                     _values;
    QString                                     _from;
    QMap<QString, QMap<QString, QString> >     _joins;
    QMap<QString, QVariant>                     _where;
    QMap<QString, bool>                         _orderBy;
    QStringList                                 _groupBy;
    int                                         _offset;
    int                                         _limit;

public:
    Query();
    virtual ~Query();

    Query* select();
    Query* insert(const QMap<QString, QVariant>& fieldValues);
    Query* update(const QMap<QString, QVariant>& fieldValues);
    Query* remove();

    Query* from(const QString& table);
    Query* into(const QString& table);
    Query* join(const QMap<QString, QMap<QString, QString> > &join);
    Query* join(const QString& table, const QMap<QString, QString>& onClauses);
    Query* where(const QMap<QString, QVariant>& where);
    Query* where(const QString &field, const QVariant &val);

    Query* orderBy(const QMap<QString, bool>& orderby);
    Query* orderBy(const QString &column, const bool ascending);
    Query* groupBy(const QStringList& groupby);
    Query* groupBy(const QString& group);
    Query* limit(const int limit, const int offset = 0);

    QString toSql() const;
};

#endif // QUERY_H
