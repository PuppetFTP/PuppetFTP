/*
 * AccessibleServerViewer.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef ACCESSIBLESERVERMODELVIEWER_H
#define ACCESSIBLESERVERMODELVIEWER_H

#include "ModelEntityViewer.h"
#include "AccessibleServer.h"


namespace UI {

class AccessibleServerModelViewer: public ModelEntityViewer< ::Model::AccessibleServer > {
public:
    AccessibleServerModelViewer();
    virtual ~AccessibleServerModelViewer();
};

} // namespace UI

#endif /* ACCESSIBLESERVERMODELVIEWER_H */
