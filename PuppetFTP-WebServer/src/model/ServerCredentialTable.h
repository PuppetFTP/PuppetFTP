/*
 * ServerCredentialTable.h
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#ifndef ServerCredentialTable_H
#define ServerCredentialTable_H

#include <QObject>
#include "Table.h"
#include "Credential.h"

class ServerCredentialTable : public Table<Model::Credential> {
public:
    ServerCredentialTable();
    virtual ~ServerCredentialTable();

    QString getName() const;
    QStringList getPrimaryKeys() const;
};

#endif // ServerCredentialTable_H
