/*
 * UserModelViewer.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#include "UserModelViewer.h"

namespace UI {

UserModelViewer::UserModelViewer() : ModelEntityViewer< ::Model::User >() {
    // title
    addPropertyToTitle("Last Name");
    addPropertyToTitle("First Name");
    addPropertyToTitle("Email");
    addPropertyToTitle("Last Access");
    // details
    removeProperty("passwd");
    removeProperty("created_at");
    removeProperty("id");
}

UserModelViewer::~UserModelViewer() {
}

} // namespace UI
