/*
 * AbstractRequestProcessor.h
 *
 *  Created on: 5 nov. 2012
 *      Author: laplace
 */

#ifndef ABSTRACTREQUESTPROCESSOR_H_
#define ABSTRACTREQUESTPROCESSOR_H_

#include <QString>
#include <QByteArray>
#include "IRequestProcessor.h"
#include "Notify.h"

class AbstractRequestProcessor : public IRequestProcessor {
public:
    UI::Notify* _notify;

public:
    AbstractRequestProcessor();
    virtual ~AbstractRequestProcessor();

    virtual QString                 getContentType()                const;
    virtual bool                    hasAdditionalHeaderParameters() const;
    virtual QHash<QString, QString> getAdditionalHeaderParameters() const;
    virtual QStringList             getRequiredCredentials()       const;
    virtual UI::Notify*             getNotify()                     const;
    virtual void                    addNotify(QPair<QString, UI::Notify::SEVERITY> notice);
    virtual void                    addNotify(const QString& text, UI::Notify::SEVERITY severity = UI::Notify::NONE);
    virtual void                    process(HTTPRequest& request)         = 0;
    virtual QByteArray              render()                        const = 0;
};

#endif // ABSTRACTREQUESTPROCESSOR_H_
