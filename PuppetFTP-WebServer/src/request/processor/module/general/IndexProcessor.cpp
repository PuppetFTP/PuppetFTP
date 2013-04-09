/*
 * ConnectionProcessor.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include "IndexProcessor.h"
#include "DefaultPageRenderer.h"
#include "OutputRendererFactory.h"
#include "SessionManager.h"
#include "Session.h"
#include "Helper.h"
#include "Widget.h"

IndexProcessor::IndexProcessor() : AbstractRequestProcessor() {
}

IndexProcessor::~IndexProcessor() {
}

void IndexProcessor::process(HTTPRequest& request) {
    Session* s = SessionManager::instance()->getSession(request.getSessionId());

    addNotify(s->getNotification("connection"));
    addNotify(s->getNotification("listing"));
}

QByteArray IndexProcessor::render() const {
    UI::DefaultPageRenderer core;
    QMap<QString, QVariant> param;

    core.setTitle("PuppetFTP - Home");
    core.body()->addWidget(_notify);

    UI::Container* divClear = new UI::Container();
    divClear->setAttribute("style", "clear:both;visibility:hidden;");
    divClear->addWidget(new UI::Text("&nbsp;"));

    // Content
    // Menu 1 - Configure PuppetFTP
    UI::Container* aside1 = new UI::Container(UI::Container::ASIDE);
    {
        aside1->setId("leftSide");
        aside1->addClass("box");

        UI::Container* divIcon1 = new UI::Container();
        {
            divIcon1->addClass("icon");

            UI::Image* img1 = new UI::Image("/images/icon_admin.png", "Configure PuppetFTP");
            img1->setAttribute("width", "70");
            divIcon1->addWidget(img1);
        }
        aside1->addWidget(divIcon1);

        UI::Container* divMenu1 = new UI::Container();
        {
            divMenu1->addClass("menu");

            param["entity"] = "user";
            UI::Menu* menu1 = new UI::Menu(UI::Container::NAV);
            menu1->addSection("configure", "Configure PuppetFTP");
            menu1->addMenu("configure", new UI::Link(Helper::gen_url("entityList", param),   new UI::Text("- Manage your users")));
            param["entity"] = "server";
            menu1->addMenu("configure", new UI::Link(Helper::gen_url("entityList", param),   new UI::Text("- Manage your available servers")));
            menu1->addMenu("configure", new UI::Link(Helper::gen_url("importExport", param), new UI::Text("- Import/Export configuration")));
            divMenu1->addWidget(menu1);
        }
        aside1->addWidget(divMenu1);

        aside1->addWidget(divClear);
    }
    core.body()->addWidget(aside1);

    // Menu 2 - Manage Your Server
    UI::Container* aside2 = new UI::Container(UI::Container::ASIDE);
    {
        aside2->setId("rightSide");
        aside2->addClass("box");

        UI::Container* divIcon2 = new UI::Container();
        {
            divIcon2->addClass("icon");

            UI::Image* img2 = new UI::Image("/images/icon_ftp.png", "Manage your servers");
            img2->setAttribute("width", "70");
            divIcon2->addWidget(img2);
        }
        aside2->addWidget(divIcon2);

        UI::Container* divMenu2 = new UI::Container();
        {
            divMenu2->addClass("menu");

            param.clear();
            UI::Menu* menu2 = new UI::Menu(UI::Container::NAV);
            menu2->addSection("server", "Manage Your Server");
            menu2->addMenu("server", new UI::Link(Helper::gen_url("serverUserList", param),   new UI::Text("- Manage your users")));
            menu2->addMenu("server", new UI::Link(Helper::gen_url("serverList", param),   new UI::Text("- Configure your servers")));
            menu2->addMenu("server", new UI::Link(Helper::gen_url("importExport", param), new UI::Text("- Import/Export configuration")));
            divMenu2->addWidget(menu2);
        }
        aside2->addWidget(divMenu2);

        aside2->addWidget(divClear);
    }
    core.body()->addWidget(aside2);

    core.body()->addWidget(divClear);

    return core.render();
}
