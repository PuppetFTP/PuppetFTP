/*
 * PuppetFTPCredentialTable.cpp
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#include "PuppetFTPCredentialTable.h"

PuppetFTPCredentialTable::PuppetFTPCredentialTable() : Table<Model::Credential>() {
}

PuppetFTPCredentialTable::~PuppetFTPCredentialTable() {
}

QString PuppetFTPCredentialTable::getName() const {
    return "puppetftp_credential";
}

QStringList PuppetFTPCredentialTable::getPrimaryKeys() const {
    QStringList pks;
    pks << "id";
    return pks;
}
