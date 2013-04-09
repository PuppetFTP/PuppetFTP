/*
 * PuppetFTPRoleTable.cpp
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#include "PuppetFTPRoleTable.h"

PuppetFTPRoleTable::PuppetFTPRoleTable() : Table<Model::Role>() {
}

PuppetFTPRoleTable::~PuppetFTPRoleTable() {
}

QString PuppetFTPRoleTable::getName() const {
    return "puppetftp_role";
}

QStringList PuppetFTPRoleTable::getPrimaryKeys() const {
    QStringList pks;
    pks << "id";
    return pks;
}
