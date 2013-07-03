/*
 * CredentialModelEditor.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "CredentialModelEditor.h"
#include "IWidget.h"
#include "Translate.h"

namespace UI {

CredentialModelEditor::CredentialModelEditor() : ModelEntityEditor< ::Model::Credential >() {
    Translate::instance()->group("editor_credential");
    getForm()->removeWidget("id");
    getForm()->getWidget("name")->setLabel(Translate::instance()->tr("name"));
}

CredentialModelEditor::~CredentialModelEditor() {
}

} // namespace UI
