/*
 * CommunicationException.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include "CommunicationException.h"

CommunicationException::CommunicationException() {
}

CommunicationException::CommunicationException(const QString& message) : _message(message) {
}

CommunicationException::CommunicationException(const CommunicationException& exception) : _message(exception.message()) {
}

CommunicationException::~CommunicationException() throw() {
}

QString CommunicationException::message() const {
    return "Communication error: " + _message;
}
