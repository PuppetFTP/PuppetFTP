/*
 * CredentialModelViewer.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "CredentialModelViewer.h"

namespace UI {

CredentialModelViewer::CredentialModelViewer() : ModelEntityViewer< ::Model::Credential >() {
    // title
    addPropertyToTitle("Name");
    // details
    removeProperty("id");
}

CredentialModelViewer::~CredentialModelViewer() {
}

} // namespace UI
