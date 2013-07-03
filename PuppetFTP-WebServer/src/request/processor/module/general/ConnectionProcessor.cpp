/*
 * ConnectionProcessor.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include <QDateTime>
#include "DefaultPageRenderer.h"
#include "OutputRendererFactory.h"
#include "ConnectionProcessor.h"
#include "SessionManager.h"
#include "Session.h"
#include "Widget.h"
#include "Helper.h"
#include "DatabaseManager.h"
#include "User.h"
#include "Translate.h"

ConnectionProcessor::ConnectionProcessor() : AbstractRequestProcessor() {
}

ConnectionProcessor::~ConnectionProcessor() {
}

void ConnectionProcessor::process(HTTPRequest& request) {
    if (!request.getParameter("submit").isNull()) {

        QString missingFields;
        if (request.getParameter("login").isNull()) {
            missingFields.append("login");
        }
        if (request.getParameter("passwd").isNull())  {
            if (!missingFields.isEmpty()) missingFields.append(", ");
            missingFields.append("password");
        }

        if (!missingFields.isEmpty()) {
            addNotify("Missing field(s) :" + missingFields, UI::Notify::WARNING);
            return;
        }

        QMap<QString, QVariant> authCouple;
        authCouple.insert("email", request.getParameter("login"));
        authCouple.insert("passwd", request.getParameter("passwd"));

        ITable*      table = DatabaseManager::instance()->getTable("user");
        Model::User* user  = dynamic_cast<Model::User*>(table->get(authCouple));
        if (user == NULL) {
            addNotify("Invalid login/password.", UI::Notify::ERROR);
            delete table;
            return;
        }
        Session* s = SessionManager::instance()->getSession(request.getSessionId());

        s->setAuthenticated(true);
        user->setLastAccess(QDateTime::currentDateTime());
        table->save(user);

        s->setNotification("connection", user->getLastname() + " is connected.", UI::Notify::INFO);
        request.redirect(Helper::gen_url("index"));
        delete table;
        delete user;
    }
}

QByteArray ConnectionProcessor::render() const {
    UI::DefaultPageRenderer core(true);

    Translate::instance()->group("connection");

    core.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));
    core.body()->addWidget(_notify);
    // Content
    UI::Container* connection = new UI::Container(UI::Container::SECTION);
    {
        connection->setId("connexion");
        connection->addClass("box");

        // Create Form
        UI::Form* form = new UI::Form(Helper::gen_url("login"));
        {
            form->setRendering(UI::Form::NONE);
            form->setRendererLabel(false);
            form->setId("connectForm");
            form->setAttribute("novalidate", "novalidate");

            // Input User
            UI::Input* user = new UI::Input("login");
            user->setLabel(Translate::instance()->tr("user"));
            user->setPlaceholder(true);
            form->addWidget("connect", user);
            // Input Password
            UI::Input* password = new UI::Input("passwd", UI::Input::PASSWORD);
            password->setLabel(Translate::instance()->tr("password"));
            password->setPlaceholder(true);
            form->addWidget("connect", password);
            // Button
            UI::Input* button = new UI::Input("submit", UI::Input::SUBMIT);
            button->setValue(Translate::instance()->tr("button"));
            button->setId("submitForm");
            button->addClass("submit btn");
            form->addWidget("connect", button);
        }
        connection->addWidget(form);
    }
    core.body()->addWidget(connection);

    return core.render();
}
