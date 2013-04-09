/*
 * ServerConfEditor.cpp
 *
 *  Created on: 19 feb. 2013
 *      Author: mtonnelier
 */

#include "ServerConfEditor.h"
#include "Helper.h"

namespace UI {

ServerConfEditor::ServerConfEditor() : ModelEntityEditor< ::UI::ServerConfWrapper >() {
    // Label
    getForm()->getWidget("server_name")->setLabel("Server name");
    getForm()->getWidget("server_port")->setLabel("Port");
    getForm()->getWidget("internet_protocol")->setLabel("Protocol");
    getForm()->getWidget("idle_timeout")->setLabel("Idle timeout");
    getForm()->getWidget("data_timeout")->setLabel("Data timeout");
//    getForm()->getWidget("use_system_user")->setLabel("Use system user");
//    getForm()->getWidget("virtual_user_auth")->setLabel("Virtual user auth");
//    getForm()->getWidget("virtual_users")->setLabel("Virtual users");
//    getForm()->getWidget("anonymous_allowed")->setLabel("Allow connection");
//    getForm()->getWidget("anonymous_upload_allowed")->setLabel("Allow upload");
//    getForm()->getWidget("anonymouse_create_dir_allowed")->setLabel("Create directory");
    getForm()->getWidget("welcome_message")->setLabel("Welcome message");
    getForm()->getWidget("log_file")->setLabel("Log file");

    // Create Custom Field
    getForm()->removeWidget("internet_protocol");
    InputChoice* selectProtocol = new InputChoice("internet_protocol", InputChoice::SELECT);
    selectProtocol->addOption("0", "IPv4");
    selectProtocol->addOption("1", "IPv6");
    selectProtocol->setLabel("Protocol");
    getForm()->addWidget("editor", selectProtocol);
    setFormat("internet_protocol", &Helper::formatEnumProtocol);

    getForm()->removeWidget("virtual_user_auth");
    InputChoice* selectVirtual = new InputChoice("virtual_user_auth", InputChoice::SELECT);
    selectVirtual->addOption("0", "Anonymous");
    selectVirtual->setLabel("Virtual user auth");
    getForm()->addWidget("editor", selectVirtual);

    // Change order
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
    getForm()->getWidget("log_file")->setAttribute("disabled", "disabled");

    // Set attribute
    getContent()->removeAttribute("class");
    getContent()->addClass("rightCol");
}

ServerConfEditor::~ServerConfEditor() {
}

} // namespace UI
