#include "abstractauthentication.h"

AbstractAuthentication::AbstractAuthentication()
{
}

bool AbstractAuthentication::addUser(const QString & user, const QString & password)
{
    if (!refresh())
        return false;

    if (m_users.contains(user))
        return false;

    m_users.insert(user, password);
    return update();
}

bool AbstractAuthentication::removeUser(const QString user)
{
    if (!refresh())
        return false;

    return (!m_users.remove(user)) ? false : update();
}

QStringList AbstractAuthentication::users()
{
    refresh();
    QStringList users;
    QHashIterator < QString, QString > it(m_users);
    while (it.hasNext()) {
        it.next();
        users << it.key();
    }

    return users;
}
