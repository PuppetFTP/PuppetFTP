/*
 * ServerListProcessor.h
 *
 *  Created on: 17 juin 2013
 *      Author: mtonnelier
 */

#ifndef SERVERLISTPROCESSOR_H
#define SERVERLISTPROCESSOR_H

#include "AbstractRequestProcessor.h"
#include "IModelList.h"

class ServerListProcessor: public AbstractRequestProcessor {
protected:
    UI::IModelList* _table;
public:
    ServerListProcessor();
    virtual ~ServerListProcessor();

    QStringList getRequiredCrendentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // SERVERLISTPROCESSOR_H
