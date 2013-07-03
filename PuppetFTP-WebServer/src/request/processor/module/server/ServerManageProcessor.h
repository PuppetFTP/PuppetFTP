/*
 * ServerManageProcessor.h
 *
 *  Created on: 17 juin 2013
 *      Author: mtonnelier
 */

#ifndef SERVEREDITPROCESSOR_H
#define SERVEREDITPROCESSOR_H

#include "AbstractRequestProcessor.h"
#include "IModelEditor.h"

class ServerManageProcessor: public AbstractRequestProcessor {
protected:
    int               _id;
    UI::IModelEditor* _form;
public:
    ServerManageProcessor();
    virtual ~ServerManageProcessor();

    QStringList getRequiredCrendentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // SERVEREDITPROCESSOR_H
