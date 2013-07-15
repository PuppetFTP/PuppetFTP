/*
 * EntityListProcessor.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: mtonnelier
 */

#include "EntityListProcessor.h"
#include "SessionManager.h"
#include "Session.h"

#include "DefaultPageRenderer.h"
#include "ModelWidgetFactory.h"
#include "UserModelList.h"
#include "Helper.h"
#include "Widget.h"
#include "ITable.h"
#include "DatabaseManager.h"
#include "Translate.h"

EntityListProcessor::EntityListProcessor() : AbstractRequestProcessor() {
}

EntityListProcessor::~EntityListProcessor() {
}

void EntityListProcessor::process(HTTPRequest& request) {
    Session* s = SessionManager::instance()->getSession(request.getSessionId());
    addNotify(s->getNotification("delete"));
    addNotify(s->getNotification("edit"));

    _type       = request.getParameter("type").toString();
    _entityName = request.getParameter("entity").toString();


    ITable* object = DatabaseManager::instance()->getTable(_entityName);
    if (object == NULL) {
        s->setNotification("listing", "Entity '"+_entityName+"' doesn't exists.", UI::Notify::ERROR);
        request.redirect("index");
        return;
    }

    _table = UI::ModelWidgetFactory::instance()->getListWidget(_entityName + "List");
    if (_table) {
        _table->fill(object->getAll());
    } else {
        s->setNotification("listing", "Model List Entity '"+_entityName+"' doesn't exists.", UI::Notify::ERROR);
        request.redirect("index");
    }
    delete object;
}

QByteArray EntityListProcessor::render() const {
    UI::DefaultPageRenderer page;
    QMap<QString, QVariant> param;
    param["entity"] = _entityName;

    page.body()->addWidget(_notify);

    Translate::instance()->group("breadcrumb");
    // Breadcrumbs
    UI::Title* title = new UI::Title();
    {
        UI::Breadcrumb* link = new UI::Breadcrumb();
        QString name(Translate::instance()->tr("entity", _entityName));
        name[0] = name[0].toUpper();

        link->addLink(Translate::instance()->tr("home"), Helper::gen_url("index"));
        link->addLink(name, Helper::gen_url("entityList", param));
        title->addWidget(link);
    }
    page.body()->addWidget(title);

    Translate::instance()->group("listing");
    page.setTitle("PuppetFTP - " + Translate::instance()->tr("title"));

    // Content
    UI::Container* divContent = new UI::Container();
    {
        // Icon
        UI::Container* divIcon = new UI::Container();
        {
            divIcon->addClass("icon users");
            UI::Image* imgContent = new UI::Image("/img/icon_admin.png", Translate::instance()->tr("icon"));
            imgContent->setAttribute("width", "60");
            divIcon->addWidget(imgContent);
        }
        divContent->addWidget(divIcon);

        // Menu
        Translate::instance()->group("listing_menu");
        UI::Menu* menu = new UI::Menu(UI::Container::NAV);
        {
            menu->setAttribute("id", "menu");
            param["entity"] = "user";
            menu->addMenu("menu", new UI::Link(Helper::gen_url("entityList", param), new UI::Text(Translate::instance()->tr("user"))));
//            param["entity"] = "server";
            menu->addMenu("menu", new UI::Link(Helper::gen_url("importExport", param), new UI::Text(Translate::instance()->tr("import_export"))));

//            param["entity"] = "role";
//            menu->addMenu("menu", new UI::Link(Helper::gen_url("entityList", param), new UI::Text(Translate::instance()->tr("role"))));
//            param["entity"] = "credential";
//            menu->addMenu("menu", new UI::Link(Helper::gen_url("entityList", param), new UI::Text(Translate::instance()->tr("credential"))));
        }
        divContent->addWidget(menu);

        // Listing
        divContent->addWidget(_table->getContent());

        // Clear
        UI::Container* divClear = new UI::Container();
        divClear->setAttribute("style", "clear:both;visibility:hidden;");
        divContent->addWidget(divClear);
    }
    page.body()->addWidget(divContent);

    return page.render();
}

