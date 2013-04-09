/*
 * DatabaseManager.cpp
 *
 *  Created on: 13 nov. 2012
 *      Author: Vince
 */

#include "DatabaseManager.h"

DatabaseManager* DatabaseManager::_instance = 0;

DatabaseManager::DatabaseManager() {
}

DatabaseManager::~DatabaseManager() {
    if (_database.isOpen())
        _database.close();
}

DatabaseManager* DatabaseManager::instance() {
    if (_instance == 0) {
        _instance = new DatabaseManager();
    }
    return _instance;
}

void DatabaseManager::destroy() {
    if (_instance != 0) {
        delete _instance;
        _instance = 0;
    }
}

bool DatabaseManager::configure(const QMap<QString, QString> &options) {
    _database = QSqlDatabase::addDatabase("QSQLITE"); //sqlite3, not sqlite!

    //database name (path)
    if (options.contains("DatabaseName"))
        _database.setDatabaseName(options["DatabaseName"]);
    else {
        QString path(QDir::current().path());
        path.append(QDir::separator()).append("config");
        path.append(QDir::separator()).append("puppet.db.sqlite");
        path = QDir::toNativeSeparators(path);
        _database.setDatabaseName(path);
    }

    //user name
    if (options.contains("UserName"))
        _database.setUserName(options["UserName"]);

    //password
    if (options.contains("Password"))
        _database.setPassword(options["Password"]);

    //sqlite-specific options
    //example : "QSQLITE_BUSY_TIMEOUT=30;QSQLITE_OPEN_READONLY=1"
    //please refer to http://doc-snapshot.qt-project.org/4.8/qsqldatabase.html#setConnectOptions
    if (options.contains("ConnectOptions"))
        _database.setConnectOptions(options["ConnectOptions"]);

    //no host nor port since sqlite doesn't support remote connections

    if (false == _database.open()) {
        qDebug() << "Failed to open database.";
        //todo
        return false;
    }

    return true;
}

QSqlQuery DatabaseManager::performQuery(const Query &query) {
    return _database.exec(query.toSql());;
}

ITable* DatabaseManager::getTable(const QString &name) const {
    return getObject(name);
}
