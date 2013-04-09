/*
 * AccessibleServerModelViewer.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "AccessibleServerModelViewer.h"

namespace UI {

AccessibleServerModelViewer::AccessibleServerModelViewer() : ModelEntityViewer< ::Model::AccessibleServer >() {
    // title
    addPropertyToTitle("User");
    addPropertyToTitle("Server");
    addPropertyToTitle("Role");
    // details
}

AccessibleServerModelViewer::~AccessibleServerModelViewer() {
}

} // namespace UI
