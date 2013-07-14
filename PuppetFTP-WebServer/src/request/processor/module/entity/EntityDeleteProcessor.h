/*
 * EntityDeleteProcessor.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ENTITYDELETEPROCESSOR_H
#define ENTITYDELETEPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"

class EntityDeleteProcessor: public AbstractRequestProcessor {
protected:
    QString     _entityName;
    int         _id;
public:
    EntityDeleteProcessor();
    virtual ~EntityDeleteProcessor();

    QStringList getRequiredCredentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // ENTITYDELETEPROCESSOR_H
