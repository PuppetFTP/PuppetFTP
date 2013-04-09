/*
 * ParsingException.cpp
 *
 *  Created on: 5 nov. 2012
 *      Author: laplace
 */

#include "ParsingException.h"

ParsingException::ParsingException() {
}

ParsingException::ParsingException(const QString& filepath, const QString& message) :
        _file(filepath), _message(message) {
}

ParsingException::~ParsingException() throw() {
}

QString ParsingException::message() const {
    return "An error occurred while parsing file '" + _file + "': " + _message;
}

