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
#include "Translate.h"

namespace UI {


UserModelEditor::UserModelEditor() : ModelEntityEditor< ::Model::User >() {
    Translate::instance()->group("editor_user");
    // Remove unsed widget
    getForm()->removeWidget("id");
    getForm()->removeWidget("created_at");
    getForm()->removeWidget("last_access");
    getForm()->removeWidget("puppetftp_role");
    getForm()->removeWidget("passwd");

    // Set label
    getForm()->getWidget("firstname")->setLabel(Translate::instance()->tr("firstname"));
    getForm()->getWidget("lastname")->setLabel(Translate::instance()->tr("lastname"));
    getForm()->getWidget("email")->setLabel(Translate::instance()->tr("mail"));

    // Add custom attribute
    getForm()->getWidget("email")->setAttribute("autocomplete", "off");

    // Get role
    initCustomField();
}

UserModelEditor::~UserModelEditor() {
}

void UserModelEditor::initCustomField() {

    ITable* table = DatabaseManager::instance()->getTable("puppetftp_role");
    if (table == NULL) {
        // rediriger ou gérer le cas d'erreur
    }

    // Create custom widget
    InputChoice* selectRole = new InputChoice("puppetftp_role", InputChoice::SELECT);
    {
        selectRole->setLabel(Translate::instance()->tr("role"));

        QList<QObject*> roles = table->getAll();
        for (QList<QObject*>::const_iterator it = roles.begin(); it != roles.end(); it++) {
            Model::Role* role = dynamic_cast<Model::Role*>(*it);
            selectRole->addOption(QString::number(role->getId()), role->getName());
        }
        roles.clear();
    }
    getForm()->addWidget("editor", selectRole);


    Input* password = new Input("passwd", Input::PASSWORD);
    {
        password->setLabel(Translate::instance()->tr("password"));
        password->setAttribute("autocomplete", "off");
    }
    getForm()->addWidget("editor", password);

    delete table;
}

} // namespace UI
