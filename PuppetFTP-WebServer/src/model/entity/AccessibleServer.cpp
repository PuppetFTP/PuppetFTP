/*
 * AccessibleServer.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include "AccessibleServer.h"

namespace Model {

AccessibleServer::AccessibleServer() {
    _user = 0;
    _server = 0;
    _role = 0;
}

AccessibleServer::~AccessibleServer() {
}

quint32 AccessibleServer::getUser()   const         { return _user;     }
quint32 AccessibleServer::getServer() const         { return _server;   }
quint32 AccessibleServer::getRole()   const         { return _role;	    }

void    AccessibleServer::setUser(quint32   user)       { _user   = user;   }
void    AccessibleServer::setServer(quint32 server)     { _server = server; }
void    AccessibleServer::setRole(quint32   role)		{ _role   = role;   }

} // namespace Model
