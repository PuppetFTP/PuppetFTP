/*
 * UserModelEditor.cpp
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#include "UserModelEditor.h"
#include "DatabaseManager.h"
#include "Role.h"
#include "Input.h"

namespace UI {


UserModelEditor::UserModelEditor() : ModelEntityEditor< ::Model::User >() {
    // Remove unsed widget
    getForm()->removeWidget("id");
    getForm()->removeWidget("created_at");
    getForm()->removeWidget("last_access");
    getForm()->removeWidget("puppetftp_role");
    getForm()->removeWidget("passwd");

    // Set label
    getForm()->getWidget("firstname")->setLabel("First Name");
    getForm()->getWidget("lastname")->setLabel("Last Name");
    getForm()->getWidget("email")->setLabel("Email");

    // Add custom attribute
    getForm()->getWidget("email")->setAttribute("autocomplete", "off");

    // Get role
    ITable*         table = DatabaseManager::instance()->getTable("puppetftp_role");
    if (table == NULL) {
        // rediriger ou gérer le cas d'erreur

    }
    QList<QObject*> roles = table->getAll();

    // Create custom widget
    InputChoice* selectRole = new InputChoice("puppetftp_role", InputChoice::SELECT);
    selectRole->setLabel("Role");

    for (QList<QObject*>::const_iterator it = roles.begin(); it != roles.end(); it++) {
        Model::Role* role = dynamic_cast<Model::Role*>(*it);
        selectRole->addOption(QString::number(role->getId()), role->getName());
    }
    getForm()->addWidget("editor", selectRole);

    Input* password = new Input("passwd", Input::PASSWORD);
    password->setLabel("Password");
    password->setAttribute("autocomplete", "off");

    getForm()->addWidget("editor", password);

    roles.clear();
    delete table;
}


UserModelEditor::~UserModelEditor() {
}

} // namespace UI
