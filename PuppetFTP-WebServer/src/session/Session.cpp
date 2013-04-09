/*
 * Session.cpp
 *
 *  Created on: 3 oct. 2012
 *      Author: laplace
 */

#include <QDebug>
#include "Session.h"
#include "SessionManager.h"

Session::Session(const QString& sessid, const QHostAddress& peer) :
	_peer(peer), _sessid(sessid), _startedAt(QDateTime::currentDateTimeUtc()), _lastActionAt(QDateTime::currentDateTimeUtc()),
	_timer(new QTimer(this)), _authenticated(false) {
    _timer->setInterval(SessionManager::instance()->getSessionTimeout() * 1000);
    _timer->setSingleShot(true);
    _timer->start();
    connect(_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(this, SIGNAL(sessionExpired(const QString&)), SessionManager::instance(), SLOT(destroySession(const QString&)));
}

Session::~Session() {
}

QHostAddress Session::getPeer() const {
    return _peer;
}

QString Session::getId() const {
    return _sessid;
}

bool Session::isAuthenticated() const {
	return _authenticated;
}

void Session::setAuthenticated(bool auth) {
	_authenticated = auth;
}

bool Session::hasCredential(const QString& right) const {
    qDebug() << right;
	return true;
}

QVariant Session::getAttribute(const QString& name) const {
    return _attributes[name];
}

QMap<QString, QVariant> Session::getAttributes() const {
    return _attributes;
}

void Session::setAttribute(const QString& name, const QVariant& value) {
    _attributes[name] = value;
}

QPair<QString, UI::Notify::SEVERITY> Session::getNotification(const QString& name) {
    if (!_notifications.contains(name)) return QPair<QString, UI::Notify::SEVERITY>();

    QPair<QString, UI::Notify::SEVERITY> tmp = _notifications[name];
    _notifications.remove(name);
    return tmp;
}

QMap<QString, QPair<QString, UI::Notify::SEVERITY> > Session::getNotifications() {
    QMap<QString, QPair<QString, UI::Notify::SEVERITY> > tmp = _notifications;
    _notifications.clear();
    return tmp;
}

void Session::setNotification(const QString& name, const QString& text, UI::Notify::SEVERITY severity) {
    QPair<QString, UI::Notify::SEVERITY> notice = qMakePair(text, severity);
    _notifications[name] = notice;
}

void Session::setNotification(const QString& name, QPair<QString, UI::Notify::SEVERITY>& notice) {
    _notifications[name] = notice;
}

void Session::clear() {
    _authenticated = false;
    _rights.clear();
    _attributes.clear();
    _notifications.clear();
}

QString Session::toCookieString() const {
    QDateTime dt = _lastActionAt.addMSecs(_timer->interval());
    return _sessid + "; Expires=" + dt.toString("ddd, dd-MMM-yyy hh:mm:ss UTC");
}

void Session::updateAccess() {
    _lastActionAt = QDateTime::currentDateTimeUtc();
    _timer->start();
}

void Session::timeout() {
    emit sessionExpired(_sessid);
}
