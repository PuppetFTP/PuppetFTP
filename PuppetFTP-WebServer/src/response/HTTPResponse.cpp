/*
 * HTTPResponse.cpp
 *
 *  Created on: 1 oct. 2012
 *      Author: laplace
 */

#include <QString>
#include <QDateTime>
#include <QDebug>
#include "HTTPResponse.h"

/**
 * Create a new response, by default, the response is OK
 */
HTTPResponse::HTTPResponse() : _status(RESPONSE_OK) {
}

HTTPResponse::~HTTPResponse() {
}

void HTTPResponse::unauthorized() {
    setStatus(RESPONSE_UNAUTHORIZED);
    setParameter("Content-Type", "text/html; charset=utf-8");
    QString content = "<html><head></head><body><h1>You are not authorized to access to this !</h1></body></html>";
    setContent(content.toLatin1());
}

void HTTPResponse::forbidden() {
    setStatus(RESPONSE_FORBIDDEN);
    setParameter("Content-Type", "text/html; charset=utf-8");
    QString content = "<html><head></head><body><h1>Access to this is forbidden !</h1></body></html>";
    setContent(content.toLatin1());
}

void HTTPResponse::error(const QString& message) {
    setStatus(RESPONSE_ERROR);
    setParameter("Content-Type", "text/html; charset=utf-8");
    QString content = "<html><head></head><body><h1>Ooops ! An error occured !</h1>";
    if (message.isEmpty() == false) {
        content += "<div>" + message + "</div>";
    }
    content += "</body></html>";
    setContent(content.toLatin1());
}

void HTTPResponse::notFound(const QString& resource) {
    setStatus(RESPONSE_NOT_FOUND);
    setParameter("Content-Type", "text/html; charset=utf-8");
    QString content = "<html><head></head><body><h1>Ooops ! The requested resource cannot be found !</h1>";
    if (resource.isEmpty() == false) {
        content += "<div>" + resource + " cannot be found.</div>";
    }
    content += "</body></html>";
    setContent(content.toLatin1());
}

void HTTPResponse::redirect(const QString& url) {
    setStatus(RESPONSE_REDIRECT);
    setParameter("Location", url);
}

HTTPResponse::Status HTTPResponse::getStatus() const { return _status; }

QString HTTPResponse::getStatusString() const {
    QString status;
    switch (_status) {
    case RESPONSE_OK:
        status = "200 OK";
        break;
    case RESPONSE_REDIRECT:
        status = "303 See Other";
        break;
    case RESPONSE_UNAUTHORIZED:
        status = "401 Unauthorized";
        break;
    case RESPONSE_FORBIDDEN:
        status = "403 Forbidden";
        break;
    case RESPONSE_NOT_FOUND:
        status = "404 Not Found";
        break;
    case RESPONSE_ERROR:
        status = "500 Internal Server Error";
        break;
    default:
        status = "";
        break;
    }
    return status;
}

QString    HTTPResponse::getParameter(const QString& name) const                 { return _parameters[name];  }
QByteArray HTTPResponse::getContent()                      const                 { return _content;           }
QString    HTTPResponse::getCookie(const QString& name)    const                 { return _cookies[name];     }

void       HTTPResponse::setStatus(const HTTPResponse::Status& status)           { _status = status;          }
void       HTTPResponse::setParameter(const QString& name, const QString& value) { _parameters[name] = value; }
void       HTTPResponse::removeParameter(const QString& name)                    { _parameters.remove(name);  }
void       HTTPResponse::setContent(const QByteArray& content)                   { _content = content; setParameter("Content-Length", QString("").setNum(_content.length())); }
void       HTTPResponse::appendContent(const QByteArray& content)                { _content += content; setParameter("Content-Length", QString("").setNum(_content.length())); }
void       HTTPResponse::setCookie(const QString& name, const QString& value)    { _cookies[name] = value; }


QByteArray HTTPResponse::toByteArray() const {
    QByteArray bytes;
    QString r = "HTTP/1.1 " + getStatusString() + "\r\n";
    for (QHash<QString, QString>::const_iterator it = _parameters.begin(); it != _parameters.end(); it++) {
        r += it.key() + ": " + it.value() + "\r\n";
    }
    for (QHash<QString, QString>::const_iterator it = _cookies.begin(); it != _cookies.end(); it++) {
        r += "Set-Cookie: " + it.key() + "=" + it.value() + "\r\n";
    }
    r += "\r\n";
    bytes.append(r);
    if (_parameters.contains("Content-Length")) {
        bytes.append(_content);
    }
    return bytes;
}

QDebug operator<<(QDebug debug, HTTPResponse& response) {
    return debug << "HTTPRequest: " << response.toByteArray();
}
