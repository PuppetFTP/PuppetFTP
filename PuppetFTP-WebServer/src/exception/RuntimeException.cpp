/*
 * RuntimeException.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#include "RuntimeException.h"

RuntimeException::RuntimeException() throw() : _message("") {
}

RuntimeException::RuntimeException(const RuntimeException& exception) throw() : _message(exception.message()) {
}

RuntimeException::RuntimeException(const QString& message) throw() : _message(message) {
}

RuntimeException::~RuntimeException() throw() {
}

QString RuntimeException::message() const throw() {
    return _message;
}
