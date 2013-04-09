/*
 * CredentialModelEditor.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "CredentialModelEditor.h"
#include "IWidget.h"

namespace UI {

CredentialModelEditor::CredentialModelEditor() : ModelEntityEditor< ::Model::Credential >() {
    getForm()->removeWidget("id");
    getForm()->getWidget("name")->setLabel("Name");
}

CredentialModelEditor::~CredentialModelEditor() {
}

} // namespace UI
