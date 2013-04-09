/*
 * ServerModelViewer.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "ServerModelViewer.h"

namespace UI {

ServerModelViewer::ServerModelViewer() : ModelEntityViewer< ::Model::Server >() {
    // title
    addPropertyToTitle("Name");
    addPropertyToTitle("Address");
    addPropertyToTitle("Port");
    // details
    removeProperty("id");
}

ServerModelViewer::~ServerModelViewer() {
}

} // namespace UI
