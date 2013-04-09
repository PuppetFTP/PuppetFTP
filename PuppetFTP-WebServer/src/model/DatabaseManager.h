/*
 * DatabaseManager.h
 *
 *  Created on: 13 nov. 2012
 *      Author: Vince
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSqlError>
#include "utils/Factory.h"
#include "ITable.h"
#include "Query.h"

class DatabaseManager : private Factory<ITable> {
private:
    DatabaseManager();
    virtual ~DatabaseManager();

    static DatabaseManager*         _instance;

    QSqlDatabase                    _database;

public:
    static DatabaseManager* instance();
    static void             destroy();

    bool configure(const QMap<QString, QString>& options);
    QSqlQuery performQuery(const Query &query);


    template<typename T>
    void registerTable(const QString& name) {
        registerObject<T>(name);
    }

    ITable* getTable(const QString &name) const;
};

#endif // DATABASEMANAGER_H
