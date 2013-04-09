/*
 * DisconnectProcessor.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#include "DisconnectProcessor.h"
#include "SessionManager.h"
#include "Session.h"

DisconnectProcessor::DisconnectProcessor() : AbstractRequestProcessor() {
}

DisconnectProcessor::~DisconnectProcessor() {
}

void DisconnectProcessor::process(HTTPRequest& request) {
    Session* s = SessionManager::instance()->getSession(request.getSessionId());
    s->clear();
    request.redirect("/connection");
}

QByteArray DisconnectProcessor::render() const {
    return QByteArray();
}

