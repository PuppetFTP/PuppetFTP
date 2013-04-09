/*
 * HTTPRequest.cpp
 *
 *  Created on: 1 oct. 2012
 *      Author: laplace
 */

#include <QStringList>
#include <QRegExp>
#include <QUrl>
#include "HTTPRequest.h"
#include "RequestDispatcher.h"

HTTPRequest::HTTPRequest() {
}

HTTPRequest::HTTPRequest(const QHostAddress& peer) : _peer(peer), _reditectTo("") {
}

HTTPRequest::~HTTPRequest() {
}

QHostAddress            HTTPRequest::getPeer()                          const { return _peer;                                  }
QString                 HTTPRequest::getRawData()                       const { return _rawData;                               }
QString                 HTTPRequest::getSessionId()                     const { return _cookies["SESSID"];                     }
QString                 HTTPRequest::getRequestedURI()                  const { return _header.path();                         }
bool                    HTTPRequest::hasParameter(const QString& name)  const { return _parameters.contains(name);             }
QVariant                HTTPRequest::getParameter(const QString& name)  const { return _parameters[name];                      }
QMap<QString, QVariant> HTTPRequest::getParameters()                    const { return _parameters;                            }

void HTTPRequest::setRawData(const QString& data)                             { _rawData = data;                               }
void HTTPRequest::appendRawData(const QString& data)                          { _rawData += data;                              }
void HTTPRequest::setSessionId(const QString& sessid)                         { _cookies["SESSID"] = sessid;                   }
void HTTPRequest::setParameter(const QString& name, const QVariant& value)    { _parameters[name] = value;                     }
void HTTPRequest::setParameters(QMap<QString, QVariant> parameters)           { _parameters.clear(); _parameters = parameters; }

void HTTPRequest::parseHeader() {
    // Parse header...
    _header = QHttpRequestHeader(_rawData);
    // Parse cookies...
    QStringList cookies = _header.value("Cookie").split(';');
    for (QStringList::iterator it = cookies.begin(); it != cookies.end(); it++) {
        QStringList tmp = (*it).trimmed().split('=');
        if (tmp.size() == 2) {
            _cookies[tmp.at(0)] = tmp.at(1);
        }
    }
}

void HTTPRequest::parseData(const Routing::Route& route) {
    QString uri = _header.path();
    QString pattern = route.getUri();
    QStringList uriParts = pattern.split('/');
    QStringList uriArgs;
    // Get argument name and prepare pattern
    for (int i = 0; i < uriParts.size(); i++) {
        if (uriParts[i].startsWith(':')) {
            try {
                QStringList t = uriParts[i].split(':');
                uriArgs << t.at(1);
                pattern = pattern.replace(uriParts[i], "("+route.getRequirement(t.at(1))+")");
            } catch (...) {
                // ignore error, pattern will not be replaced
            }
        }
    }
    // If route has arguments, find them
    if (uriArgs.size()) {
        QRegExp rx(pattern);
        int pos = 0;
        rx.indexIn(uri, pos);
        QStringList capture = rx.capturedTexts();
        for (int i = 0; i < uriArgs.size(); i++) {
            _parameters[uriArgs.at(i)] = QString(capture.at(i + 1));
        }
    }

    // Parse post data
    QString post = _rawData.split("\r\n\r\n").at(1);
    if (post.isEmpty() == false) {
        QStringList args = post.split("&");
        for (QStringList::iterator it = args.begin(); it != args.end(); it++) {
            QStringList arg = (*it).split("=");
            if (arg.at(0).isEmpty() == false) {
                _parameters[arg.at(0)] = QString(QUrl::fromPercentEncoding(arg.at(1).toLatin1()));
            }
        }
    }
}

void HTTPRequest::redirect(const QString& uri) {
    _reditectTo = uri;
}

bool HTTPRequest::isRedirected() const {
    return _reditectTo != "";
}

QString HTTPRequest::getRedirection() const {
    return _reditectTo;
}

QString HTTPRequest::toString() const {
    return _header.toString();
}

QDebug operator<<(QDebug debug, const HTTPRequest& request) {
    return debug << "HTTPRequest: " << request.toString();
}

HTTPRequest& operator<<(HTTPRequest& request, const QString& data) {
    request.appendRawData(data);
    return request;
}
