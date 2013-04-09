/*
 * ParsingException.h
 *
 *  Created on: 5 nov. 2012
 *      Author: laplace
 */

#ifndef PARSINGEXCEPTION_H_
#define PARSINGEXCEPTION_H_

#include <exception>
#include <QString>

class ParsingException: public std::exception {
private:
    ParsingException();

    QString _file;
    QString _message;

public:
    ParsingException(const QString& filepath, const QString& message);
    virtual ~ParsingException() throw();

    QString message() const;
};

#endif /* PARSINGEXCEPTION_H_ */
