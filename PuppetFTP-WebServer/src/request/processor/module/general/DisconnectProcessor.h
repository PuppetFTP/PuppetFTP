/*
 * DisconnectProcessor.h
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#ifndef DISCONNECTPROCESSOR_H_
#define DISCONNECTPROCESSOR_H_

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"

class DisconnectProcessor: public AbstractRequestProcessor {
public:
    DisconnectProcessor();
    virtual ~DisconnectProcessor();

    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif /* DISCONNECTPROCESSOR_H_ */
