/*
 * Role.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include "Role.h"

namespace Model {

Role::Role() {
    _id = 0;
}

Role::~Role() {
}

quint32            Role::getId()                            const                 { return _id;                       }
QString            Role::getName()                          const                 { return _name;                     }
QString            Role::getDescription()                   const                 { return _description;              }

void               Role::setId(quint32 id)                                        { _id   = id;                       }
void               Role::setName(const QString& name)                             { _name = name;                     }
void               Role::setDescription(const QString& description)               { _description = description;       }

} // namespace Model
