/*
 * Credential.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include "Credential.h"

namespace Model {

Credential::Credential() {
    _id = 0;
}

Credential::~Credential() {
}

quint32 Credential::getId()   const              { return _id;          }
QString Credential::getName() const              { return _name;        }
QString Credential::getDescription() const       { return _description; }

void    Credential::setId(quint32 id)                               { _id   = id;                   }
void    Credential::setName(const QString& name)                    { _name = name;                 }
void    Credential::setDescription(const QString& description)      { _description = description;   }

} // namespace Model
