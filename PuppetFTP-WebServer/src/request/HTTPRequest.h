/*
 * HTTPRequest.h
 *
 *  Created on: 1 oct. 2012
 *      Author: laplace
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QHttpRequestHeader>
#include "Route.h"

/********************************************************************************
 * Simple class used to manage HTTP request.
 */
class HTTPRequest {
protected:
    QHostAddress            _peer;
    QHttpRequestHeader      _header;
    QMap<QString, QString>  _cookies;
    QString                 _rawData;
    QMap<QString, QVariant> _parameters;

    QString                 _redirectTo;

    HTTPRequest();

public:
    HTTPRequest(const QHostAddress& peer);
    virtual ~HTTPRequest();

    QHostAddress            getPeer()                                                 const;
    QString                 getRawData()                                              const;
    QString                 getSessionId()                                            const;
    QString                 getRequestedURI()                                         const;
    bool                    hasParameter(const QString& name)                         const;
    QVariant                getParameter(const QString& name)                         const;
    QMap<QString, QVariant> getParameters()                                           const;

    void                    setRawData(const QString& data);
    void                    appendRawData(const QString& data);
    void                    setSessionId(const QString& sessid);
    void                    setParameter(const QString& name, const QVariant& value);
    void                    setParameters(QMap<QString, QVariant> parameters);

    void                    parseHeader();
    void                    parseData(const Routing::Route& route);

    void                    redirect(const QString& uri);
    bool                    isRedirected() const;
    QString                 getRedirection() const;

    QString                 toString()                                                const;
};

QDebug       operator<<(QDebug debug, const HTTPRequest& request);
HTTPRequest& operator<<(HTTPRequest& request, const QString& data);

#endif /* HTTPREQUEST_H_ */
