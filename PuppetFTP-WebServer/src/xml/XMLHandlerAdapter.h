/*
 * XMLHandlerAdapter.h
 *
 *  Created on: 4 nov. 2012
 *      Author: laplace
 */

#ifndef XMLHANDLERADAPTER_H_
#define XMLHANDLERADAPTER_H_

#include <QString>
#include <QXmlContentHandler>
#include <QXmlErrorHandler>

/**
 * This adapter provide a default implementation for each method defined by QXmlContentHandler
 * and QXmlErrorHandler. This class allows the user to define only what he needs.
 */
class XMLHandlerAdapter : public QXmlContentHandler, public QXmlErrorHandler {
protected:
    QString _inputfile;

public:
    XMLHandlerAdapter();
    virtual ~XMLHandlerAdapter();

    // QXmlContentHandler
    virtual bool startDocument();
    virtual bool endDocument();
    virtual bool startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts);
    virtual bool endElement(const QString & namespaceURI, const QString & localName, const QString & qName);
    virtual bool characters(const QString & ch);
    virtual bool endPrefixMapping(const QString & prefix);
    virtual QString errorString() const;
    virtual bool ignorableWhitespace(const QString & ch);
    virtual bool processingInstruction(const QString & target, const QString & data);
    virtual void setDocumentLocator(QXmlLocator * locator);
    virtual bool skippedEntity(const QString & name);
    virtual bool startPrefixMapping(const QString & prefix, const QString & uri);

    // QXmlErrorHandler
    virtual bool error(const QXmlParseException& exception);
    virtual bool fatalError(const QXmlParseException& exception);
    virtual bool warning(const QXmlParseException& exception);
};

#endif /* XMLHANDLERADAPTER_H_ */
