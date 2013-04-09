/*
 * Server.h
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <QObject>
#include <QString>

namespace Model {

class Server : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32     id       READ getId      WRITE setId      )
    Q_PROPERTY(QString     name     READ getName    WRITE setName    )
    Q_PROPERTY(QString     address  READ getAddress WRITE setAddress )
    Q_PROPERTY(quint16     port     READ getPort    WRITE setPort    )
    Q_PROPERTY(QString     corba_id READ getCorbaId WRITE setCorbaId )

protected:
    quint32     _id;
    QString     _name;
    QString     _address;
    quint16     _port;
    QString     _corba_id;

public:
    Server();
    virtual ~Server();

    Q_INVOKABLE quint32     getId()      const;
    Q_INVOKABLE QString     getName()    const;
    Q_INVOKABLE QString     getAddress() const;
    Q_INVOKABLE quint16     getPort()    const;
    Q_INVOKABLE QString     getCorbaId() const;

    Q_INVOKABLE void        setId(quint32 id);
    Q_INVOKABLE void        setName(const QString& name);
    Q_INVOKABLE void        setAddress(const QString& address);
    Q_INVOKABLE void        setPort(quint16 port);
    Q_INVOKABLE void        setCorbaId(const QString& corbaId);
};

} // namespace Model

#endif /* SERVER_H_ */
