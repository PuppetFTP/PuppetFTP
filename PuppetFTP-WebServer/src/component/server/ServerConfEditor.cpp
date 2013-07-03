/*
 * ServerConfEditor.cpp
 *
 *  Created on: 19 feb. 2013
 *      Author: mtonnelier
 */

#include "ServerConfEditor.h"
#include "Helper.h"
#include "Translate.h"

namespace UI {

ServerConfEditor::ServerConfEditor() : ModelEntityEditor< ::UI::ServerConfWrapper >() {
    // Create Custom Field
    initCustomField();

    // Change order
    initOrder();

    QList<IWidgetForm*> widget = getForm()->getWidgets();

    for (QList<IWidgetForm*>::iterator it = widget.begin(); it != widget.end(); it++) {
        Translate::instance()->group("server_editor_label");
        (*it)->setLabel(Translate::instance()->tr((*it)->getName()));
        Translate::instance()->group("server_editor_help");
        (*it)->setHelp(Translate::instance()->tr((*it)->getName()));
    }
}

ServerConfEditor::~ServerConfEditor() {
}

void ServerConfEditor::initCustomField() {
    getForm()->removeWidget("internet_protocol");
    getForm()->removeWidget("virtual_user_auth");

    InputChoice* selectProtocol = new InputChoice("internet_protocol", InputChoice::SELECT);
    {
        selectProtocol->addOption("0", "IPv4");
        selectProtocol->addOption("1", "IPv6");
    }
    getForm()->addWidget("editor", selectProtocol);
    setFormat("internet_protocol", &Helper::formatEnumProtocol);

    InputChoice* selectVirtual = new InputChoice("virtual_user_auth", InputChoice::SELECT);
    {
        selectVirtual->addOption("0", "Anonymous");
    }
    getForm()->addWidget("editor", selectVirtual);

    getForm()->getWidget("log_file")->setAttribute("disabled", "disabled");

    // Set attribute
    getContent()->removeAttribute("class");
    getContent()->addClass("rightCol");
}

void ServerConfEditor::initOrder() {

    getForm()->removeAllSections();
    getForm()->addSection("network",    "Network Management");
//    getForm()->addSection("user",       "User Management");
//    getForm()->addSection("anonymous",  "Anonymous User");
    getForm()->addSection("miscs",      "Miscs");
    getForm()->addSection("submit",     "");

    QList<QString> order;
    order << "server_name" << "server_port" << "internet_protocol" << "idle_timeout" << "data_timeout";
    getForm()->setFieldOrder("network", order);
//    order.clear();
//    order << "use_system_user" << "virtual_user_auth" << "virtual_users";
//    getForm()->setFieldOrder("user", order);
//    order.clear();
//    order << "anonymous_allowed" << "anonymous_upload_allowed" << "anonymouse_create_dir_allowed";
//    getForm()->setFieldOrder("anonymous", order);
    order.clear();
    order << "welcome_message" << "log_file";
    getForm()->setFieldOrder("miscs", order);
}

} // namespace UI
