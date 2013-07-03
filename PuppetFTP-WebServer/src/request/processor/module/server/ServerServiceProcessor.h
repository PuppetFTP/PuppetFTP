/*
 * ServerServiceProcessor.h
 *
 *  Created on: 17 juin 2013
 *      Author: mtonnelier
 */

#ifndef SERVERSERVICEPROCESSOR_H
#define SERVERSERVICEPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"

class ServerServiceProcessor: public AbstractRequestProcessor {
protected:
    QString     _name;
    int         _id;
    bool        _close;
public:
    ServerServiceProcessor();
    virtual ~ServerServiceProcessor();

    QStringList getRequiredCrendentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // SERVERSERVICEPROCESSOR_H
