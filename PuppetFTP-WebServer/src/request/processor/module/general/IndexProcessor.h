/*
 * IndexProcessor.h
 *
 *  Created on: 11 nov. 2012
 *      Author: mtonnelier
 */

#ifndef INDEXPROCESSOR_H
#define INDEXPROCESSOR_H

#include "AbstractRequestProcessor.h"


class IndexProcessor: public AbstractRequestProcessor {
private:
    QString _sessionID;
public:
    IndexProcessor();
    virtual ~IndexProcessor();

    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // INDEXPROCESSOR_H
