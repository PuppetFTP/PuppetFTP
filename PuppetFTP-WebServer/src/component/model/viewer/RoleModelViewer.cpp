/*
 * RoleModelViewer.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "RoleModelViewer.h"

namespace UI {

RoleModelViewer::RoleModelViewer() : ModelEntityViewer< ::Model::Role >() {
    // title
    addPropertyToTitle("Name");
    // details
    removeProperty("id");
}

RoleModelViewer::~RoleModelViewer() {
}

} // namespace UI
