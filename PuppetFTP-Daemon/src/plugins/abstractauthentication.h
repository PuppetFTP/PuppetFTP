#ifndef ABSTRACTAUTHENTICATION_H
#define ABSTRACTAUTHENTICATION_H

#include <QStringList>
#include <QHash>

typedef QHash < QString, QString > Users;

class AbstractAuthentication
{
public:
    AbstractAuthentication();
    bool addUser(const QString & user, const QString & password);
    bool removeUser(const QString user);
    QStringList users();

protected:
    virtual bool update() = 0;
    virtual bool refresh() = 0;

protected:
    Users m_users;
};

#endif // ABSTRACTAUTHENTICATION_H
