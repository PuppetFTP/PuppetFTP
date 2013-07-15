/*
 * ServerForm.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "ServerModelEditor.h"
#include "IWidget.h"
#include "Translate.h"

namespace UI {

ServerModelEditor::ServerModelEditor() : ModelEntityEditor< ::Model::Server >() {
    Translate::instance()->group("editor_server");
    getForm()->removeWidget("id");
    getForm()->getWidget("name")->setLabel(Translate::instance()->tr("name"));
    getForm()->getWidget("address")->setLabel(Translate::instance()->tr("address"));
    getForm()->getWidget("port")->setLabel(Translate::instance()->tr("port"));
    getForm()->getWidget("corba_id")->setLabel(Translate::instance()->tr("ref_id"));
}

ServerModelEditor::~ServerModelEditor() {
}

} // namespace UI
