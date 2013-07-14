#ifndef SERVERSERVICEPROCESSOR_H
#define SERVERSERVICEPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"

class ServerServiceProcessor: public AbstractRequestProcessor {
protected:
    QString     _name;
    int         _id;
public:
    ServerServiceProcessor();
    virtual ~ServerServiceProcessor();

    QStringList getRequiredCredentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // SERVERSERVICEPROCESSOR_H
