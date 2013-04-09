/*
 * RoleModelEditor.h
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#ifndef ROLEMODELEDITOR_H
#define ROLEMODELEDITOR_H

#include "ModelEntityEditor.h"
#include "Role.h"


namespace UI {

class RoleModelEditor : public ModelEntityEditor< ::Model::Role > {
public:
    RoleModelEditor();
    virtual ~RoleModelEditor();
};

} // namespace UI

#endif /* ROLEMODELEDITOR_H */
