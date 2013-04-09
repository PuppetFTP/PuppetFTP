/*
 * User.h
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#ifndef USER_H_
#define USER_H_

#include <QObject>
#include <QString>
#include <QDateTime>

namespace Model {

class User : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32   id                 READ getId         WRITE setId        )
    Q_PROPERTY(QString   firstname          READ getFirstname  WRITE setFirstname )
    Q_PROPERTY(QString   lastname           READ getLastname   WRITE setLastname  )
    Q_PROPERTY(QString   email              READ getEmail      WRITE setEmail     )
    Q_PROPERTY(QString   passwd             READ getPasswd     WRITE setPasswd    )
    Q_PROPERTY(quint32   puppetftp_role     READ getRole       WRITE setRole      )
    Q_PROPERTY(QDateTime created_at         READ getCreatedAt  WRITE setCreatedAt )
    Q_PROPERTY(QDateTime last_access        READ getLastAccess WRITE setLastAccess)
protected:
    quint32         _id;
    QString         _firstname;
    QString         _lastname;
    QString         _email;
    QString         _passwd;
    quint32         _role;
    QDateTime       _created_at;
    QDateTime       _last_access;

public:
    User();
    virtual ~User();

    Q_INVOKABLE quint32         getId()              const;
    Q_INVOKABLE QString         getFirstname()       const;
    Q_INVOKABLE QString         getLastname()        const;
    Q_INVOKABLE QString         getEmail()           const;
    Q_INVOKABLE QString         getPasswd()          const;
    Q_INVOKABLE quint32         getRole()            const;
    Q_INVOKABLE QDateTime       getCreatedAt()       const;
    Q_INVOKABLE QDateTime       getLastAccess()      const;

    Q_INVOKABLE void            setId(quint32 id);
    Q_INVOKABLE void            setFirstname(QString firstname);
    Q_INVOKABLE void            setLastname(QString lastname);
    Q_INVOKABLE void            setEmail(QString email);
    Q_INVOKABLE void            setPasswd(QString passwd);
    Q_INVOKABLE void            setRole(quint32 role);
    Q_INVOKABLE void            setCreatedAt(QDateTime createdAt);
    Q_INVOKABLE void            setLastAccess(QDateTime lastAccess);
};

} // namespace Model

#endif /* USER_H_ */
