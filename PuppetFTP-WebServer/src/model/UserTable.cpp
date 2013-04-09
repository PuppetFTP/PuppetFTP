/*
 * UserTable.cpp
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#include "UserTable.h"

UserTable::UserTable() : Table<Model::User>() {
}

UserTable::~UserTable() {
}

QString UserTable::getName() const {
    return "user";
}

QStringList UserTable::getPrimaryKeys() const {
    QStringList pks;
    pks << "id";
    return pks;
}
