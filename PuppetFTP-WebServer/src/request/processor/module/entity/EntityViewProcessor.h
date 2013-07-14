/*
 * EntityViewProcessor.h
 *
 *  Created on: 11 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ENTITYVIEWPROCESSOR_H
#define ENTITYVIEWPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"

class EntityViewProcessor: public AbstractRequestProcessor {
protected:
    QString _type;
public:
    EntityViewProcessor();
    virtual ~EntityViewProcessor();

    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // ENTITYVIEWPROCESSOR_H
