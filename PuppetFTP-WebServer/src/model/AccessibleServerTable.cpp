/*
 * AccessibleServerTable.cpp
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#include "AccessibleServerTable.h"

AccessibleServerTable::AccessibleServerTable() : Table<Model::AccessibleServer>() {
}

AccessibleServerTable::~AccessibleServerTable() {
}

QString AccessibleServerTable::getName() const {
    return "accessible_server";
}

QStringList AccessibleServerTable::getPrimaryKeys() const {
    QStringList pks;
    pks << "user" << "server" << "role";
    return pks;
}
