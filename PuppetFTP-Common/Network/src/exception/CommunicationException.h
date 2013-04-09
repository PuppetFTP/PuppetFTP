/*
 * CommunicationException.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef COMMUNICATIONEXCEPTION_H_
#define COMMUNICATIONEXCEPTION_H_

#include <string>
#include <QString>

class CommunicationException {
private:
    QString _message;

public:
    CommunicationException();
    CommunicationException(const QString& message);
    CommunicationException(const CommunicationException& exception);
    virtual ~CommunicationException() throw();

    virtual QString message() const;
};

#endif // COMMUNICATIONEXCEPTION_H_
