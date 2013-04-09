/*
 * ResourceProcessor.h
 *
 *  Created on: 12 déc. 2012
 *      Author: laplace
 */

#ifndef RESOURCEPROCESSOR_H_
#define RESOURCEPROCESSOR_H_

#include <QHash>
#include <QFile>
#include "IRequestProcessor.h"

class ResourceProcessor: public IRequestProcessor {
private:
    QHash<QString, QString> _headerParameters;
    QString                 _contentType;
    QFile                   _resource;
    QByteArray              _bytes;

public:
    ResourceProcessor();
    virtual ~ResourceProcessor();

    QString                 getContentType() const;
    bool                    hasAdditionalHeaderParameters() const;
    QHash<QString, QString> getAdditionalHeaderParameters() const;
    QStringList             getRequiredCrendentials() const;
    UI::Notify*             getNotify() const;

    void                    process(HTTPRequest& request);
    QByteArray              render() const;
};

#endif /* RESOURCEPROCESSOR_H_ */
