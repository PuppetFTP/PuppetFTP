#ifndef UNAVAILABLEPROCESSOR_H
#define UNAVAILABLEPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"

class UnavailableProcessor: public AbstractRequestProcessor {
protected:

public:
    UnavailableProcessor();
    virtual ~UnavailableProcessor();

    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // UNAVAILABLEPROCESSOR_H
