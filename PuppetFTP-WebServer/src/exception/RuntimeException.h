/*
 * RuntimeException.h
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#ifndef RUNTIMEEXCEPTION_H_
#define RUNTIMEEXCEPTION_H_

#include <QString>

class RuntimeException : public std::exception {
private:
    QString _message;

public:
    RuntimeException()                             throw();
    RuntimeException(const RuntimeException&)      throw();
    RuntimeException(const QString& message = "")  throw();
    virtual ~RuntimeException()                    throw();

    virtual QString message() const                throw();
};

#endif /* RUNTIMEEXCEPTION_H_ */
