/*
 * EntityDeleteProcessor.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "EntityDeleteProcessor.h"
#include "SessionManager.h"
#include "Session.h"

#include "EmptyPageRenderer.h"
#include "DatabaseManager.h"
#include "ITable.h"
#include "Helper.h"
#include "Widget.h"
#include "Translate.h"

EntityDeleteProcessor::EntityDeleteProcessor() : AbstractRequestProcessor() {
}

EntityDeleteProcessor::~EntityDeleteProcessor() {
}

void EntityDeleteProcessor::process(HTTPRequest& request) {
    _id         = request.getParameter("id").toInt();
    _entityName = request.getParameter("entity").toString();
    Session*  s = SessionManager::instance()->getSession(request.getSessionId());
    _close      = false;

    QMap<QString, QVariant> param;
    param.insert("entity", _entityName);

    ITable*  table  = DatabaseManager::instance()->getTable(_entityName);
    QObject* object = table->get("id", _id);
    if (object == NULL) {
        s->setNotification("delete", "Error: " + _entityName + " id doesn't exists.", UI::Notify::ERROR);
    } else if (!request.getParameter("submit").isNull()) {
        if (!table->remove(object)) {
            s->setNotification("delete", _entityName + " " + QString::number(_id) + " cannot be deleted.", UI::Notify::ERROR);
        } else {
            s->setNotification("delete", _entityName + " " + QString::number(_id) + " has been deleted.", UI::Notify::INFO);
        }
    }

    if (!request.getParameter("cancel").isNull() || !request.getParameter("submit").isNull() || object == NULL) {
        _close = true;
    }

    if (object != NULL) {
        delete object;
    }
    delete table;
}

QByteArray EntityDeleteProcessor::render() const {
    UI::EmptyPageRenderer page;

    if (_close == false) {

        QMap<QString, QVariant> param;
        param["entity"] = _entityName;
        param["id"]     = _id;

        Translate::instance()->group("delete");
        page.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));

        // Content
        UI::Container* divContent = new UI::Container(UI::Container::SECTION);
        {
            divContent->setId("action");
            // Deleting
            UI::Container* div = new UI::Container();
            {
                div->addClass("box");
                // Create Form
                UI::Form* form = new UI::Form(Helper::gen_url("entityDelete", param));
                {
                    form->setRendering(UI::Form::NONE);
                    form->setRendererLabel(false);
                    form->setId("deleteForm");
                    form->setAttribute("novalidate", "novalidate");
                    form->addSection("deleteForm", Translate::instance()->tr("message", _entityName + " : #" + QString::number(_id)));

                    // Submit
                    UI::Input* submit = new UI::Input("submit", UI::Input::SUBMIT);
                    submit->setValue(Translate::instance()->tr("submit"));
                    submit->addClass("btn");
                    form->addWidget("deleteForm", submit);

                    // Cancel
                    UI::Input* cancel = new UI::Input("cancel", UI::Input::SUBMIT);
                    cancel->setValue(Translate::instance()->tr("cancel"));
                    cancel->addClass("btn");
                    form->addWidget("deleteForm", cancel);

                }
                div->addWidget(form);

                // Clear
                UI::Container* divClear = new UI::Container();
                divClear->setAttribute("style", "clear:both;visibility:hidden;");
                div->addWidget(divClear);
            }
            divContent->addWidget(div);
        }
        page.body()->addWidget(divContent);
    } else {
        page.addJavascript("/js/close-sbx.js");
    }
    return page.render();
}
