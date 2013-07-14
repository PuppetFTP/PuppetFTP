/*
 * EntityEditProcessor.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ENTITYEDITPROCESSOR_H
#define ENTITYEDITPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"
#include "IModelEditor.h"

class EntityEditProcessor: public AbstractRequestProcessor {
protected:
    QString     _entityName;
    int         _id;
    UI::IModelEditor*  _form;
public:
    EntityEditProcessor();
    virtual ~EntityEditProcessor();

    QStringList getRequiredCredentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // ENTITYEDITPROCESSOR_H
