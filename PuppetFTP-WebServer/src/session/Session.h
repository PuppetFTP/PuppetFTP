/*
 * Session.h
 *
 *  Created on: 3 oct. 2012
 *      Author: laplace
 */

#ifndef SESSION_H_
#define SESSION_H_

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QDateTime>
#include <QTimer>
#include <QHostAddress>
#include "Notify.h"

class Session : public QObject {
    Q_OBJECT
private:
    QHostAddress            _peer;
	QString                 _sessid;
	QDateTime               _startedAt;
	QDateTime               _lastActionAt;
	QTimer*                 _timer;
	bool                    _authenticated;
	QStringList             _rights;
	QMap<QString, QVariant> _attributes;
    QMap<QString, QPair<QString, UI::Notify::SEVERITY> >  _notifications;

public:
	Session(const QString& sessid,const QHostAddress& peer);
	virtual ~Session();

	QHostAddress            getPeer() const;
	QString                 getId() const;

	bool                    isAuthenticated() const;
	void                    setAuthenticated(bool auth);
	bool                    hasCredential(const QString& right) const;
    void                    setCredentials(const QStringList& rights);

	QVariant                getAttribute(const QString& name) const;
	QMap<QString, QVariant> getAttributes() const;
	void                    setAttribute(const QString& name, const QVariant& value);

    QPair<QString, UI::Notify::SEVERITY>                 getNotification(const QString& name);
    QMap<QString, QPair<QString, UI::Notify::SEVERITY> > getNotifications();
    void                    setNotification(const QString& name, const QString& value, UI::Notify::SEVERITY severity = UI::Notify::NONE);
    void                    setNotification(const QString& name, QPair<QString, UI::Notify::SEVERITY>& notice);

    void                    clear();

	QString                 toCookieString() const;

	void                    updateAccess();

public slots:
    void timeout();

signals:
    void sessionExpired(const QString& sessid);
};

#endif /* SESSION_H_ */
