/*
 * IModelList.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef IMODELLIST_H
#define IMODELLIST_H

#include <QObject>
#include "Widget.h"
#include "IModelEntity.h"

namespace UI {

class IModelList : public IModelEntity {
public:
    virtual ~IModelList() {}
    virtual void fill(const QList<QObject*>& objects) = 0;
    virtual Container* getContent()             const = 0;
};

} // namespace UI

#endif // IMODELLIST_H
