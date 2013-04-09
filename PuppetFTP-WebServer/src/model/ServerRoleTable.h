/*
 * ServerRoleTable.h
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#ifndef ServerRoleTable_H
#define ServerRoleTable_H

#include <QObject>
#include "Table.h"
#include "Role.h"

class ServerRoleTable : public Table<Model::Role> {
public:
    ServerRoleTable();
    virtual ~ServerRoleTable();

    QString getName() const;
    QStringList getPrimaryKeys() const;
};

#endif // ServerRoleTable_H
