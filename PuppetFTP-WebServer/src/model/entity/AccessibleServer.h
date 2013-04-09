/*
 * AccessibleServer.h
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#ifndef ACCESSIBLESERVER_H_
#define ACCESSIBLESERVER_H_

#include <QObject>

namespace Model {

class AccessibleServer : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32  user    READ getUser   WRITE setUser           )
    Q_PROPERTY(quint32  server  READ getServer WRITE setServer         )
    Q_PROPERTY(quint32  role    READ getRole   WRITE setRole           )

protected:
    quint32     _user;
    quint32     _server;
    quint32     _role;

public:
    AccessibleServer();
    virtual ~AccessibleServer();

    Q_INVOKABLE quint32         getUser()            const;
    Q_INVOKABLE quint32         getServer()          const;
    Q_INVOKABLE quint32         getRole()            const;

    Q_INVOKABLE void             setUser(quint32 user);
    Q_INVOKABLE void             setServer(quint32 server);
    Q_INVOKABLE void             setRole(quint32 role);
};

} // namespace Model

#endif /* ACCESSIBLESERVER_H_ */
