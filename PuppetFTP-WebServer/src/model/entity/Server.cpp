/*
 * Server.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include "Server.h"

namespace Model {

Server::Server() {
    _id = 0;
}

Server::~Server() {
}

quint32     Server::getId()      const                 { return _id;          }
QString     Server::getName()    const                 { return _name;        }
QString     Server::getAddress() const                 { return _address;     }
quint16     Server::getPort()    const                 { return _port;        }
QString     Server::getCorbaId() const                 { return _corba_id;    }

void        Server::setId(quint32 id)                  { _id       = id;      }
void        Server::setName(const QString& name)       { _name     = name;    }
void        Server::setAddress(const QString& address) { _address  = address; }
void        Server::setPort(quint16 port)              { _port     = port;    }
void        Server::setCorbaId(const QString& corbaId) { _corba_id = corbaId; }

} // namespace Model
