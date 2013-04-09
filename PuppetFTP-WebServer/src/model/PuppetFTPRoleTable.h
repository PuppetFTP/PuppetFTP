/*
 * PuppetFTPRoleTable.h
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#ifndef PuppetFTPRoleTable_H
#define PuppetFTPRoleTable_H

#include <QObject>
#include "Table.h"
#include "Role.h"

class PuppetFTPRoleTable : public Table<Model::Role> {
public:
    PuppetFTPRoleTable();
    virtual ~PuppetFTPRoleTable();

    QString getName() const;
    QStringList getPrimaryKeys() const;
};

#endif // PuppetFTPRoleTable_H
