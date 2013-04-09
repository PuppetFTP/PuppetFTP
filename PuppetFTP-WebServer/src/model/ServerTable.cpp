/*
 * ServerTable.cpp
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#include "ServerTable.h"

ServerTable::ServerTable() : Table<Model::Server>() {
}

ServerTable::~ServerTable() {
}

QString ServerTable::getName() const {
    return "server";
}

QStringList ServerTable::getPrimaryKeys() const {
    QStringList pks;
    pks << "id";
    return pks;
}
