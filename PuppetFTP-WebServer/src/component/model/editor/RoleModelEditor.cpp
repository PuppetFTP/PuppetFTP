/*
 * RoleModelEditor.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "RoleModelEditor.h"
#include "IWidget.h"

namespace UI {

RoleModelEditor::RoleModelEditor() : ModelEntityEditor< ::Model::Role >() {
    getForm()->removeWidget("id");
    getForm()->getWidget("name")->setLabel("Name");
}

RoleModelEditor::~RoleModelEditor() {
}

} // namespace UI
