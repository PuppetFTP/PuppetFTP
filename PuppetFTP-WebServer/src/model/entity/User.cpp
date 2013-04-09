/*
 * User.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include "User.h"

namespace Model {

User::User() {
    _id = 0;
}

User::~User() {
}

quint32         User::getId()              const                       { return _id;                }
QString         User::getFirstname()       const                       { return _firstname;         }
QString         User::getLastname()        const                       { return _lastname;          }
QString         User::getEmail()           const                       { return _email;             }
QString         User::getPasswd()          const                       { return _passwd;            }
quint32         User::getRole()            const                       { return _role;              }
QDateTime       User::getCreatedAt()       const                       { return _created_at;        }
QDateTime       User::getLastAccess()      const                       { return _last_access;       }

void            User::setId(quint32 id)                                { _id          = id;         }
void            User::setFirstname(QString firstname)                  { _firstname   = firstname;  }
void            User::setLastname(QString lastname)                    { _lastname    = lastname;   }
void            User::setEmail(QString email)                          { _email       = email;      }
void            User::setPasswd(QString passwd)                        { _passwd      = passwd;     }
void            User::setRole(quint32 role)                            { _role        = role;       }
void            User::setCreatedAt(QDateTime createdAt)                { _created_at  = createdAt;  }
void            User::setLastAccess(QDateTime lastAccess)              { _last_access = lastAccess; }


} // namespace Model

