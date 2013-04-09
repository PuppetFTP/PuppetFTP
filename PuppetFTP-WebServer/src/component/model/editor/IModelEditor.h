/*
 * IModelEditor.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef IMODELEDITOR_H
#define IMODELEDITOR_H

#include <QObject>
#include "Widget.h"
#include "IModelEntity.h"

namespace UI {

/**
 * Only for type restriction
 */
class IModelEditor : public IModelEntity {
public:
    virtual ~IModelEditor() {}
    virtual void       bind(QObject* entity) = 0;
    virtual Form*      getForm()       const = 0;
    virtual Container* getContent()    const = 0;
};

} // namespace UI

#endif /* IMODELEDITOR_H */
