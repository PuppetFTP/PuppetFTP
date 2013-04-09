/*
 * UserTable.h
 *
 *  Created on: 13 dec. 2012
 *      Author: Vince
 */

#ifndef USERTABLE_H
#define USERTABLE_H

#include "Table.h"
#include "User.h"

class UserTable : public Table<Model::User> {
public:
    UserTable();
    virtual ~UserTable();

    QString getName() const;
    QStringList getPrimaryKeys() const;
};

#endif // USERTABLE_H
