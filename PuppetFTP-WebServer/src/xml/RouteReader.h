/*
 * RouteReader.h
 *
 *  Created on: 4 nov. 2012
 *      Author: laplace
 */

#ifndef ROUTEREADER_H_
#define ROUTEREADER_H_

#include <QString>
#include <QList>
#include "XMLHandlerAdapter.h"
#include "Route.h"

class RouteReader : public XMLHandlerAdapter {
private:
    RouteReader();

    Routing::Route*           _currentRoute;
    QPair<QString, QString>*  _currentParameter;
    QList<Routing::Route*>    _results;

public:
    RouteReader(const QString& filepath);
    virtual ~RouteReader();

    QList<Routing::Route*> parse();
    bool startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts);
    bool endElement(const QString & namespaceURI, const QString & localName, const QString & qName);
};

#endif /* ROUTEREADER_H_ */
