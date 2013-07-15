/*
 * RouteReader.cpp
 *
 *  Created on: 4 nov. 2012
 *      Author: laplace
 */

#include <QDebug>
#include <QXmlSimpleReader>
#include <QXmlInputSource>
#include <QFileInfo>
#include <QFile>
#include "RouteReader.h"
#include "ParsingException.h"

RouteReader::RouteReader() {
}

RouteReader::RouteReader(const QString& filepath) : _currentRoute(0) {
    _inputfile = filepath;
}

RouteReader::~RouteReader() {
}

QList<Routing::Route*> RouteReader::parse() {
    QFileInfo inputInfo(_inputfile);
    if (inputInfo.exists() == false || inputInfo.isReadable() == false)
        throw ParsingException(inputInfo.fileName(), "File does not exist or is not readable");
    if (inputInfo.isDir() == true || inputInfo.completeSuffix() != "xml")
        throw ParsingException(inputInfo.fileName(), "File is not a valid XML file");
    QXmlSimpleReader reader;
    QFile* source = new QFile(inputInfo.absoluteFilePath());
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    reader.parse(QXmlInputSource(source));
    delete source;
    return _results;
}

bool RouteReader::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts) {
    for (int i = 0; i << atts.length(); i++) {
        qDebug().nospace() << "  attribute #" << i << ": " << atts.qName(i) << " value: " << atts.value(i);
    }
    if (qName == "route") {
        if (atts.value("name") == "" || atts.value("uri") == "") {
            qWarning() << "Route name or route uri missing, ignored.";
        }
        else {
            _currentRoute = new Routing::Route(atts.value("name"));
            _currentRoute->setUri(atts.value("uri"));
        }
    }
    else if (qName == "module") {
        if (_currentRoute == 0) {
            qWarning() << "Invalid position of node module, ignored.";
        }
        else if (atts.value("name") == "") {
            qWarning() << "Module name missing, ignored.";
        }
        else {
            _currentRoute->setModule(atts.value("name"));
        }
    }
    else if (qName == "processor") {
        if (_currentRoute == 0) {
            qWarning() << "Invalid position of node processor, ignored.";
        }
        else if (atts.value("name") == "") {
            qWarning() << "Processor name missing, ignored.";
        }
        else {
            _currentRoute->setProcessor(atts.value("name"));
        }
    }
    else if (qName == "parameter") {
        if (_currentRoute == 0) {
            qWarning() << "Invalid position of node parameter, ignored.";
        }
        else {
            if (atts.value("name") == "" || atts.value("value") == "") {
                qWarning() << "Parameter name or value missing, ignored.";
            }
            else {
                _currentRoute->setRequirement(atts.value("name"), atts.value("value"));
            }
        }
    }
    else if (qName == "access") {
        if (_currentRoute == 0) {
            qWarning() << "Invalid position of node access, ignored.";
        }
        else {
            if (atts.value("parameter_name") == "" && atts.value("parameter_value") == "") {
                _currentParameter = 0;
            }
            else if ((atts.value("parameter_name") == "") ^ (atts.value("parameter_value") == "")) {
                qWarning() << "Parameter parameter_name or parameter_value missing, ignored.";
            }
            else {
                _currentParameter = new QPair<QString, QString>(atts.value("parameter_name"), atts.value("parameter_value"));
            }
        }
    }
    else if (qName == "credential") {
        if (_currentRoute == 0) {
            qWarning() << "Invalid position of node credential, ignored.";
        }
        else {
            if (atts.value("value") == "") {
                qWarning() << "Parameter name or value missing, ignored.";
            }
            else {
                if (_currentParameter == 0)
                    _currentRoute->setDefaultRequiredCredential(atts.value("value"));
                else
                    _currentRoute->setRequiredCredential(*_currentParameter, atts.value("value"));
            }
        }
    }
    return true;
}

bool RouteReader::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
    if (qName == "route") {
        _results.push_back(_currentRoute);
        _currentRoute = 0;
    }
    else if (qName == "access") {
        _currentParameter = 0;
    }
    return true;
}
