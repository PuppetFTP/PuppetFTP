/*
 * RoleModelEditor.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "RoleModelEditor.h"
#include "IWidget.h"
#include "Translate.h"

namespace UI {

RoleModelEditor::RoleModelEditor() : ModelEntityEditor< ::Model::Role >() {
    Translate::instance()->group("editor_role");
    getForm()->removeWidget("id");
    getForm()->getWidget("name")->setLabel(Translate::instance()->tr("name"));
}

RoleModelEditor::~RoleModelEditor() {
}

} // namespace UI
