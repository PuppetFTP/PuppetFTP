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
#include "Translate.h"

IndexProcessor::IndexProcessor() : AbstractRequestProcessor() {
}

IndexProcessor::~IndexProcessor() {
}

void IndexProcessor::process(HTTPRequest& request) {
    Session* s = SessionManager::instance()->getSession(request.getSessionId());

    QString lang = request.getParameter("lang").toString();
    if (!lang.isEmpty()) {
        Translate::instance()->load(lang);
    }

    addNotify(s->getNotification("connection"));
    addNotify(s->getNotification("listing"));
}

QByteArray IndexProcessor::render() const {
    UI::DefaultPageRenderer core;
    QMap<QString, QVariant> param;

    Translate::instance()->group("index");
    core.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));
    core.body()->addWidget(_notify);

    UI::Container* divClear = new UI::Container();
    divClear->setAttribute("style", "clear:both;visibility:hidden;");
    divClear->addWidget(new UI::Text("&nbsp;"));

    // Content
    // Menu 1 - Configure PuppetFTP
    UI::Container* section = new UI::Container(UI::Container::SECTION);
    {
        section->setId("home");

        UI::Container* divIcon1 = new UI::Container();
        {
            divIcon1->addClass("index");

            UI::Image* img = new UI::Image("/img/icon_user.png", Translate::instance()->tr("manage_users"));
            img->setAttribute("width", "60");
            divIcon1->addWidget(img);
            UI::Link* link = new UI::Link(Helper::gen_url("serverUserList", param),   new UI::Text(Translate::instance()->tr("manage_users")));
            divIcon1->addWidget(link);
        }
        section->addWidget(divIcon1);

        UI::Container* divIcon2 = new UI::Container();
        {
            divIcon2->addClass("index");

            UI::Image* img = new UI::Image("/img/icon_ftp.png", Translate::instance()->tr("manage_servers"));
            img->setAttribute("width", "60");
            divIcon2->addWidget(img);
            UI::Link* link = new UI::Link(Helper::gen_url("serverList", param),   new UI::Text(Translate::instance()->tr("manage_servers")));
            divIcon2->addWidget(link);
        }
        section->addWidget(divIcon2);

        UI::Container* divIcon3 = new UI::Container();
        {
            divIcon3->addClass("index");

            UI::Image* img = new UI::Image("/img/icon_import.png", Translate::instance()->tr("manage_import_export"));
            img->setAttribute("width", "60");
            divIcon3->addWidget(img);
            UI::Link* link = new UI::Link(Helper::gen_url("importExport", param),   new UI::Text(Translate::instance()->tr("manage_import_export")));
            divIcon3->addWidget(link);
        }
        section->addWidget(divIcon3);

        section->addWidget(divClear);
    }
    core.body()->addWidget(section);

    core.body()->addWidget(divClear);

    return core.render();
}
