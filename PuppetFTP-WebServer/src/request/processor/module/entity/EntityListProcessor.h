/*
 * EntityListProcessor.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ENTITYLISTPROCESSOR_H
#define ENTITYLISTPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"
#include "IModelList.h"

class EntityListProcessor: public AbstractRequestProcessor {
protected:
    QString         _type;
    QString         _entityName;
    UI::IModelList* _table;

public:
    EntityListProcessor();
    virtual ~EntityListProcessor();

    QStringList getRequiredCrendentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // ENTITYLISTPROCESSOR_H
