/*
 * AbstractRequestProcessor.cpp
 *
 *  Created on: 5 nov. 2012
 *      Author: laplace
 */

#include "AbstractRequestProcessor.h"

AbstractRequestProcessor::AbstractRequestProcessor() {
    _notify = NULL;
}

AbstractRequestProcessor::~AbstractRequestProcessor() {
    if (_notify != NULL) {
        delete _notify;
    }
}

QString AbstractRequestProcessor::getContentType() const { return "text/html; charset=utf-8"; }

bool AbstractRequestProcessor::hasAdditionalHeaderParameters() const {
    return false;
}

QHash<QString, QString> AbstractRequestProcessor::getAdditionalHeaderParameters() const {
    return QHash<QString, QString>();
}

UI::Notify* AbstractRequestProcessor::getNotify() const {
    return _notify;
}

void AbstractRequestProcessor::addNotify(QPair<QString, UI::Notify::SEVERITY> notice) {
    if (!notice.first.isNull() && !notice.first.isEmpty()) {
        addNotify(notice.first, notice.second);
    }
}

void AbstractRequestProcessor::addNotify(const QString& text, UI::Notify::SEVERITY severity) {
    if (_notify == NULL) {
        _notify = new UI::Notify();
    }
    _notify->addNotice(text, severity);
}
