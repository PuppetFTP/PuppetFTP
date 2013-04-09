/*
 * ServerCredentialTable.cpp
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#include "ServerCredentialTable.h"

ServerCredentialTable::ServerCredentialTable() : Table<Model::Credential>() {
}

ServerCredentialTable::~ServerCredentialTable() {
}

QString ServerCredentialTable::getName() const {
    return "server_credential";
}

QStringList ServerCredentialTable::getPrimaryKeys() const {
    QStringList pks;
    pks << "id";
    return pks;
}
