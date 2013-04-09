/*
 * IRequestProcessor.h
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#ifndef IREQUESTPROCESSOR_H_
#define IREQUESTPROCESSOR_H_

#include <QString>
#include <QByteArray>
#include <QStringList>
#include <QHash>
#include "HTTPRequest.h"
#include "Notify.h"

class IRequestProcessor {
public:
    virtual ~IRequestProcessor() {}

    virtual QString                 getContentType()                const  = 0;
    virtual bool                    hasAdditionalHeaderParameters() const  = 0;
    virtual QHash<QString, QString> getAdditionalHeaderParameters() const  = 0;
    virtual QStringList             getRequiredCrendentials()       const  = 0;
    virtual UI::Notify*             getNotify()                     const  = 0;
    virtual void                    process(HTTPRequest& request)          = 0;
    virtual QByteArray              render()                        const  = 0;
};

#endif // IREQUESTPROCESSOR_H_
