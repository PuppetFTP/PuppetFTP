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

QList<QObject*> PuppetFTPCredentialTable::getCredentialsForRole(int roleId) const {
    Query q;
    QMap<QString, QString> joinClause;
    joinClause.insert("puppetftp_credential", "id");
    q.select()->from(getName())->join("puppetftp_role_credential", joinClause)->where("puppetftp_role", roleId);
    return rawToObjects(DatabaseManager::instance()->performQuery(q));
}
