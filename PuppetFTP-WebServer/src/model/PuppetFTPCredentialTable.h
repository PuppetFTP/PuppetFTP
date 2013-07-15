/*
 * PuppetFTPCredentialTable.h
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#ifndef PuppetFTPCredentialTable_H
#define PuppetFTPCredentialTable_H

#include <QObject>
#include "Table.h"
#include "Credential.h"

class PuppetFTPCredentialTable : public Table<Model::Credential> {
public:
    PuppetFTPCredentialTable();
    virtual ~PuppetFTPCredentialTable();

    QString getName() const;
    QStringList getPrimaryKeys() const;
    QList<QObject*> getCredentialsForRole(int roleId) const;
};

#endif // PuppetFTPCredentialTable_H
