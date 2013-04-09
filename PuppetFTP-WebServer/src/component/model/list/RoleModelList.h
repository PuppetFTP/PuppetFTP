/*
 * RoleModelList.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ROLEMODELLIST_H
#define ROLEMODELLIST_H

#include "ModelEntityList.h"
#include "Role.h"
#include "IWidget.h"

namespace UI {

class RoleModelList : public ModelEntityList< ::Model::Role > {
public:
    RoleModelList();
    virtual ~RoleModelList();
};

} // namespace UI

#endif /* ROLEMODELLIST_H */
