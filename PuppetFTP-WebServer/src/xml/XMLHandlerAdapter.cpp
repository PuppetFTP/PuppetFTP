/*
 * XMLHandlerAdapter.cpp
 *
 *  Created on: 4 nov. 2012
 *      Author: laplace
 */

#include <QDebug>
#include "XMLHandlerAdapter.h"
#include "ParsingException.h"

XMLHandlerAdapter::XMLHandlerAdapter() {
}

XMLHandlerAdapter::~XMLHandlerAdapter() {
}

bool XMLHandlerAdapter::startDocument() { return true; }
bool XMLHandlerAdapter::endDocument() { return true; }
bool XMLHandlerAdapter::startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts) { return true; }
bool XMLHandlerAdapter::endElement(const QString & namespaceURI, const QString & localName, const QString & qName) { return true; }
bool XMLHandlerAdapter::error(const QXmlParseException& exception) { qCritical().nospace() << "While reading " << _inputfile << ": " << exception.message(); return false; }
bool XMLHandlerAdapter::fatalError(const QXmlParseException& exception) { throw ParsingException(_inputfile, exception.message()); return false; }
bool XMLHandlerAdapter::warning(const QXmlParseException& exception) { qWarning().nospace() << "While reading " << _inputfile << ": " << exception.message(); return true; }
bool XMLHandlerAdapter::characters(const QString& ch) { return true; }
bool XMLHandlerAdapter::endPrefixMapping(const QString& prefix) { return true; }
bool XMLHandlerAdapter::ignorableWhitespace(const QString& ch) { return true; }
bool XMLHandlerAdapter::processingInstruction(const QString& target, const QString& data) { return true; }
void XMLHandlerAdapter::setDocumentLocator(QXmlLocator* locator) {}
bool XMLHandlerAdapter::skippedEntity(const QString& name) { return true; }
bool XMLHandlerAdapter::startPrefixMapping(const QString& prefix, const QString& uri) { return true; }
QString XMLHandlerAdapter::errorString() const { return ""; }
