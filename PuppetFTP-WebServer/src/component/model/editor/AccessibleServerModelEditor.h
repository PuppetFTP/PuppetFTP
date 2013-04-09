/*
 * AccessibleServerModelEditor.h
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#ifndef ACCESSIBLESERVERMODELEDITOR_H
#define ACCESSIBLESERVERMODELEDITOR_H

#include "ModelEntityEditor.h"
#include "AccessibleServer.h"

namespace UI {

class AccessibleServerModelEditor : public ModelEntityEditor< ::Model::AccessibleServer > {
public:
    AccessibleServerModelEditor();
    virtual ~AccessibleServerModelEditor();
};

} // namespace UI

#endif /* ACCESSIBLESERVERMODELEDITOR_H */
