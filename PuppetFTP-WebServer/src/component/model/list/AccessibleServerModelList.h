/*
 * AccessibleServerModelList.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ACCESSIBLESERVERMODELLIST_H
#define ACCESSIBLESERVERMODELLIST_H

#include "ModelEntityList.h"
#include "AccessibleServer.h"
#include "IWidget.h"

namespace UI {

class AccessibleServerModelList : public ModelEntityList< ::Model::AccessibleServer > {
public:
    AccessibleServerModelList();
    virtual ~AccessibleServerModelList();
};

} // namespace UI

#endif /* ACCESSIBLESERVERMODELLIST_H */
