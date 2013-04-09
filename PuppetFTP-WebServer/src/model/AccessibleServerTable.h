/*
 * AccessibleServerTable.h
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#ifndef ACCESSIBLESERVER_H
#define ACCESSIBLESERVER_H

#include <QObject>
#include "Table.h"
#include "AccessibleServer.h"

class AccessibleServerTable : public Table<Model::AccessibleServer> {
public:
    AccessibleServerTable();
    virtual ~AccessibleServerTable();

    QString getName() const;
    QStringList getPrimaryKeys() const;
};

#endif // ACCESSIBLESERVER_H
