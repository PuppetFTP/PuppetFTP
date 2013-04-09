/*
 * RoleModelViewer.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ROLEMODELVIEWER_H
#define ROLEMODELVIEWER_H

#include "ModelEntityViewer.h"
#include "Role.h"


namespace UI {

class RoleModelViewer: public ModelEntityViewer< ::Model::Role > {
public:
    RoleModelViewer();
    virtual ~RoleModelViewer();
};

} // namespace UI

#endif /* ROLEMODELVIEWER_H */
