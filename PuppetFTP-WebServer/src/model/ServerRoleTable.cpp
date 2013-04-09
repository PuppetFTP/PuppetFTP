/*
 * ServerRoleTable.cpp
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#include "ServerRoleTable.h"

ServerRoleTable::ServerRoleTable() : Table<Model::Role>() {
}

ServerRoleTable::~ServerRoleTable() {
}

QString ServerRoleTable::getName() const {
    return "server_role";
}

QStringList ServerRoleTable::getPrimaryKeys() const {
    QStringList pks;
    pks << "id";
    return pks;
}
