/*
 * EntityEditProcessor.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include <QMetaProperty>
#include "EntityEditProcessor.h"
#include "SessionManager.h"
#include "Session.h"
#include "EmptyPageRenderer.h"
#include "Helper.h"
#include "Widget.h"
#include "ModelWidgetFactory.h"
#include "ModelEntityFactory.h"
#include "ITable.h"
#include "DatabaseManager.h"
#include "Translate.h"

EntityEditProcessor::EntityEditProcessor() : AbstractRequestProcessor() {
}

EntityEditProcessor::~EntityEditProcessor() {
}

QStringList EntityEditProcessor::getRequiredCrendentials() const {
    QStringList list;
    return list;
}

void EntityEditProcessor::process(HTTPRequest& request) {
    _id         = request.getParameter("id").toInt();
    _entityName = request.getParameter("entity").toString();
    Session*  s = SessionManager::instance()->getSession(request.getSessionId());
    _close      = false;

    addNotify(s->getNotification("edit"));
    QString url;
    QMap<QString, QVariant> param;
    param.insert("entity", _entityName);

    if (_id) {
        param.insert("id", _id);
        url = Helper::gen_url("entityEdit", param);
    } else {
        url = Helper::gen_url("entityAdd", param);
    }
    _form = UI::ModelWidgetFactory::instance()->getEditorWidget(_entityName + "Editor");
    if (_form == NULL){
        s->setNotification("edit", "Model Form Entity '"+_entityName+"' doesn't exists.", UI::Notify::ERROR);
//        request.redirect(Helper::gen_url("entityList", param));
        _close = true;
        return;
    }
    _form->getForm()->setAction(url);

    ITable*  table  = DatabaseManager::instance()->getTable(_entityName);
    if (table == NULL) {
        s->setNotification("edit", _entityName+" doesn't exists.", UI::Notify::ERROR);
//        request.redirect(Helper::gen_url("entityList", param));
        _close = true;
        return;
    }
    QObject* object = 0;
    if (_id) {
        object = table->get("id", _id);
        if (object == NULL) {
            s->setNotification("edit", _entityName+" id " + QString::number(_id) + " doesn't exists.", UI::Notify::ERROR);
//            request.redirect(Helper::gen_url("entityAdd", param));
            _close = true;
            delete table;
            return;
        }
    } else {
        object = Model::ModelEntityFactory::instance()->getEntity(_entityName);
        if (object == NULL) {
            s->setNotification("edit", _entityName+" doesn't exists.", UI::Notify::ERROR);
//            request.redirect(Helper::gen_url("entityList", param));
            _close = true;
            delete table;
            return;
        }
    }

    if (!request.getParameter("submit").isNull()) {
        for (int i = 0; i < object->metaObject()->propertyCount(); i++) {
            QMetaProperty field;
            field = object->metaObject()->property(i);
            if (request.hasParameter(field.name())) {
                field.write(object, QVariant(request.getParameter(field.name())));
            }
        }
        if (!table->save(object)) {
            s->setNotification("edit", _entityName + " " + QString::number(_id) + " cannot be saved.", UI::Notify::ERROR);
        } else {
            s->setNotification("edit", _entityName + " " + QString::number(_id) + " has been saved.", UI::Notify::INFO);
        }
        _close = true;
    }

    _form->bind(object);
    delete object;
    delete table;
}

QByteArray EntityEditProcessor::render() const {
    UI::EmptyPageRenderer page;

    if (_close == false) {

        // Header
        UI::Title* title = new UI::Title();
        {
            if (_id == 0) {
                title->addWidget(new UI::Text("Add " + _entityName));
            } else {
                title->addWidget(new UI::Text("Edit " + _entityName));
            }
        }
        page.body()->addWidget(title);

        // Content
        UI::Container* divContent = new UI::Container(UI::Container::SECTION);
        {
            divContent->setId("edition");
            // Editing
            divContent->addWidget(_form->getContent());

            // Clear
            UI::Container* divClear = new UI::Container();
            divClear->setAttribute("style", "clear:both;visibility:hidden;");
            divContent->addWidget(divClear);
        }
        page.body()->addWidget(divContent);
    } else {
        page.addJavascript("/js/close-sbx.js");
    }
    return page.render();
}
