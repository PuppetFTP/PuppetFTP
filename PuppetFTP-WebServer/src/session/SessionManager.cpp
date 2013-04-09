/*
 * SessionManager.cpp
 *
 *  Created on: 3 oct. 2012
 *      Author: laplace
 */

#include <QCryptographicHash>
#include <QUuid>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include "SessionManager.h"

SessionManager* SessionManager::_instance               = 0;
quint32         SessionManager::DEFAULT_SESSION_TIMEOUT = 30;

SessionManager::SessionManager() :
    _sessionTimeout(DEFAULT_SESSION_TIMEOUT) {
}

SessionManager::~SessionManager() {
}

SessionManager* SessionManager::instance() {
    if (_instance == 0) {
        _instance = new SessionManager();
    }
    return _instance;
}

Session* SessionManager::newSession(const QHostAddress& peer) {
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(QUuid::createUuid().toByteArray());
    hash.addData(peer.toString().toAscii());
    hash.addData(QDateTime::currentDateTimeUtc().toString("MM/dd/yyyy hh:mm:ss").toAscii());
    QString  sessid   = hash.result().toHex();
    Session* session  = new Session(sessid, peer);
    _sessions[sessid] = session;
    return session;
}

Session* SessionManager::getSession(const QString& sessid, const QHostAddress& peer) {
    if (_sessions.contains(sessid) && _sessions[sessid]->getPeer() == peer)
        return _sessions[sessid];
    return 0;
}

Session* SessionManager::getSession(const QString& sessid) {
    if (_sessions.contains(sessid)) {
        return _sessions[sessid];
    }
    return 0;
}

quint32 SessionManager::getSessionTimeout() const {
    return _sessionTimeout;
}

void SessionManager::setSessionTimeout(quint32 timeout) {
    _sessionTimeout = timeout;
}

void SessionManager::destroySession(const QString& sessid) {
    qDebug() << sessid << "expired";
    Session* session = _sessions[sessid];
    _sessions.remove(sessid);
    delete session;
}

void SessionManager::destroySession(Session& session) {
    qDebug() << session.getId();
}

