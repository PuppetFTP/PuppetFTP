/*
 * SessionManager.h
 *
 *  Created on: 3 oct. 2012
 *      Author: laplace
 */

#ifndef SESSIONMANAGER_H_
#define SESSIONMANAGER_H_

#include <QObject>
#include <QString>
#include <QHash>
#include <QHostAddress>
#include "Session.h"


class SessionManager : public QObject {
    Q_OBJECT
private:
    static SessionManager*   _instance;

    quint32                  _sessionTimeout;
    QHash<QString, Session*> _sessions;

    SessionManager();
    virtual ~SessionManager();

public:
	static quint32         DEFAULT_SESSION_TIMEOUT;

	static SessionManager* instance();
	Session* newSession(const QHostAddress& peer);
	Session* getSession(const QString& sessid, const QHostAddress& peer);
	Session* getSession(const QString& sessid);

	quint32 getSessionTimeout() const;
	void    setSessionTimeout(quint32 timeout);

public slots:
	void    destroySession(const QString& sessid);
	void    destroySession(Session& session);
};

#endif /* SESSIONMANAGER_H_ */
