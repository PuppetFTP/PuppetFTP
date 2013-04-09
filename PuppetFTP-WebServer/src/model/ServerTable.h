/*
 * ServerTable.h
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#ifndef SERVERTABLE_H
#define SERVERTABLE_H

#include <QObject>
#include "Table.h"
#include "Server.h"

class ServerTable : public Table<Model::Server> {
public:
    ServerTable();
    virtual ~ServerTable();

    QString getName() const;
    QStringList getPrimaryKeys() const;
};

#endif // SERVERTABLE_H
