/*
 * HTTPResponse.h
 *
 *  Created on: 1 oct. 2012
 *      Author: laplace
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <QString>
#include <QHash>
#include <QTextStream>
#include <QDateTime>
#include <QByteArray>

/********************************************************************************
 * Simple class used to manage HTTP response.
 */
class HTTPResponse {
public:
    enum Status {
        RESPONSE_OK,            // 200 OK
        RESPONSE_REDIRECT,      // 303 See Other
        RESPONSE_UNAUTHORIZED,  // 401 Unauthorized
        RESPONSE_FORBIDDEN,     // 403 Forbidden
        RESPONSE_NOT_FOUND,     // 404 Not Found
        RESPONSE_ERROR          // 500 Internal Server Error
    };

protected:
    Status                 _status;
    QHash<QString, QString> _parameters;
    QHash<QString, QString> _cookies;
	QByteArray             _content;

public:
	HTTPResponse();
	virtual ~HTTPResponse();

	void       unauthorized();
	void       forbidden();
	void       error(const QString& message = "");
	void       notFound(const QString& resource = "");
	void       redirect(const QString& url = "/");

    Status     getStatus()                       const;
    QString    getStatusString()                 const;
    QString    getParameter(const QString& name) const;
    QByteArray getContent()                      const;
    QString    getCookie(const QString& name)    const;

    void       setStatus(const Status& status);
    void       setParameter(const QString& name, const QString& value);
    void       removeParameter(const QString& name);
    void       setContent(const QByteArray& content);
    void       appendContent(const QByteArray& content);
    void       setCookie(const QString& name, const QString& value);

    QByteArray toByteArray() const;
};

QDebug        operator<<(QDebug debug,    HTTPResponse& response);


#endif /* HTTPRESPONSE_H_ */
