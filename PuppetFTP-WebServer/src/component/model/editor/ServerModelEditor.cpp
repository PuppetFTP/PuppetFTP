/*
 * ServerForm.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "ServerModelEditor.h"
#include "IWidget.h"

namespace UI {

ServerModelEditor::ServerModelEditor() : ModelEntityEditor< ::Model::Server >() {
    getForm()->removeWidget("id");
    getForm()->getWidget("name")->setLabel("Name");
    getForm()->getWidget("address")->setLabel("Address");
    getForm()->getWidget("port")->setLabel("Port");
    getForm()->getWidget("corba_id")->setLabel("Daemon Reference");
}

ServerModelEditor::~ServerModelEditor() {
}

} // namespace UI
