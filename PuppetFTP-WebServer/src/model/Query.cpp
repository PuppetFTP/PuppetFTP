/*
 * Query.cpp
 *
 *  Created on: 13 nov. 2012
 *      Author: Vince
 */

#include "Query.h"

Query::Query() {
    _limit = 0;
    _offset = 0;
}

Query::~Query() {
}

Query* Query::select() {
    _type = Query::SELECT;
    return this;
}

Query* Query::insert(const QMap<QString, QVariant>& fieldsValues) {
    _type = Query::INSERT;
    if (!_values.isEmpty())
        _values.clear();
    _values = QMap<QString, QVariant>(fieldsValues);
    return this;
}

Query* Query::update(const QMap<QString, QVariant>& fieldsValues) {
    _type = Query::UPDATE;
    if (!_values.isEmpty())
        _values.clear();
    _values = QMap<QString, QVariant>(fieldsValues);
    return this;
}

Query* Query::remove() {
    _type = Query::REMOVE;
    return this;
}



Query* Query::from(const QString &table) {
    _from = QString(table);
    return this;
}

Query* Query::into(const QString &table) {
    _from = QString(table);
    return this;
}

Query* Query::join(const QMap<QString, QMap<QString, QVariant> > &joins) {
    _joins = QMap<QString, QMap<QString, QVariant> >(joins);
    return this;
}

Query* Query::join(const QString &table, const QMap<QString, QVariant> &onClauses) {
    _joins[QString(table)] = QMap<QString, QVariant>(onClauses);
    return this;
}

Query* Query::where(const QMap<QString, QVariant> &where) {
    _where = QMap<QString, QVariant>(where);
    return this;
}

Query* Query::where(const QString &field, const QVariant &val) {
    _where[QString(field)] = QVariant(val);
    return this;
}


Query* Query::orderBy(const QMap<QString, bool> &orderby) {
    _orderBy = QMap<QString, bool>(orderby);
    return this;
}

Query* Query::orderBy(const QString &column, const bool ascending) {
    _orderBy[QString(column)] = ascending;
    return this;
}

Query* Query::groupBy(const QStringList &groups) {
    _groupBy = QStringList(groups);
    return this;
}

Query* Query::groupBy(const QString &group) {
    _groupBy << group;
    return this;
}

Query* Query::limit(const int limit, const int offset) {
    _limit = limit;
    _offset = offset;
    return this;
}

QString Query::toSql() const {
    QString sql = QString("");

    //base
    switch (_type) {
        case Query::SELECT :
            sql += "SELECT * FROM " + _from + " ";
        break;
        case Query::INSERT :
            sql += "INSERT INTO " + _from + " ";
            break;
        case Query::UPDATE :
            sql += "UPDATE " + _from + " ";
            break;
        case Query::REMOVE :
            sql += "DELETE FROM " + _from + " ";
            break;
    }

    //join
    if (_type == Query::SELECT && !_joins.isEmpty()) {
        for (QMap<QString, QMap<QString, QVariant> >::const_iterator it = _joins.begin(); it != _joins.end(); ++it) {
            sql += " JOIN " + it.key() + " ON ( ";
            int condNum = 0;
            for (QMap<QString, QVariant>::const_iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
                sql += ++condNum == 1 ? " " : " AND ";
                sql += it2.key() + " = " + (it2.value() == 0 ? "NULL " : "'" + it2.value().toString() + "'");
            }
            sql += " ) ";
        }
    }

    //values
    if (_type == Query::INSERT) {
        int condNum = 0;
        QString columns, values;
        for (QMap<QString, QVariant>::const_iterator it = _values.begin(); it != _values.end(); ++it) {
            columns += (++condNum == 1 ? " " : ", ") + it.key();
            values += QString(condNum == 1 ? " " : ", ") + "'" + it.value().toString() + "'";
        }
        sql += "( " + columns + " ) VALUES ( " + values + " )";
    } else if (_type == Query::UPDATE) {
        int condNum = 0;
        sql += " SET ";
        for (QMap<QString, QVariant>::const_iterator it = _values.begin(); it != _values.end(); ++it) {
            sql += ++condNum == 1 ? " " : ", ";
            sql += it.key() + " = " + "'" + it.value().toString() + "'";
        }
    }

    //where
    if (_type != Query::INSERT && !_where.isEmpty()) {
        sql += " WHERE ";
        int condNum = 0;
        for (QMap<QString, QVariant>::const_iterator it = _where.begin(); it != _where.end(); ++it) {
            sql += ++condNum == 1 ? " " : " AND ";
            sql += it.key() + " = " + (it.value() == 0 ? "NULL " : "'" + it.value().toString() + "'");
        }
    }

    //group by
    if (_type == Query::SELECT && !_groupBy.isEmpty()) {
        sql += " GROUP BY ";
        for (int i = 0; i < _groupBy.count(); ++i)
            sql += QString(i == 0 ? " " : ", ") + _groupBy[i];
    }


    //order by
    if (_type == Query::SELECT && !_orderBy.isEmpty()) {
        sql += " ORDER BY ";
        int condNum = 0;
        for (QMap<QString, bool>::const_iterator it = _orderBy.begin(); it != _orderBy.end(); ++it) {
            sql += ++condNum == 1 ? " " : ", ";
            sql += it.key() + (it.value() ? " ASC " : " DESC ");
        }
    }

    //limit
    if (_limit > 0 && _offset >= 0) {
        sql += " LIMIT " + QString::number(_limit) + " OFFSET " + QString::number(_offset);
    }


    return sql;
}
