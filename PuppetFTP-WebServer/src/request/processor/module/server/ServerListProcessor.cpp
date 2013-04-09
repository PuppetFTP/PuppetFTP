#include "ServerListProcessor.h"
#include "DefaultPageRenderer.h"
#include "ModelWidgetFactory.h"
#include "DatabaseManager.h"
#include "Widget.h"
#include "Helper.h"
#include "Session.h"
#include "SessionManager.h"

ServerListProcessor::ServerListProcessor() : AbstractRequestProcessor() {
}

ServerListProcessor::~ServerListProcessor() {
}

QStringList ServerListProcessor::getRequiredCrendentials() const {
    QStringList list;
    return list;
}

void ServerListProcessor::process(HTTPRequest& request) {
    Session*     s = SessionManager::instance()->getSession(request.getSessionId());
    addNotify(s->getNotification("edit"));

    ITable* object = DatabaseManager::instance()->getTable("server");
    if (object == 0) {
        s->setNotification("listing", "Entity 'server' doesn't exists.", UI::Notify::ERROR);
        request.redirect("index");
        return;
    }

    _table = UI::ModelWidgetFactory::instance()->getListWidget("serverConfigurationList");
    if (_table == NULL) {
        s->setNotification("listing", "Model Entity List 'serverConfiguration' doesn't exists.", UI::Notify::ERROR);
        request.redirect("index");
    } else {
        _table->fill(object->getAll());
    }
    delete object;
}

QByteArray ServerListProcessor::render() const {
    UI::DefaultPageRenderer page;
    QMap<QString, QVariant> param;

    page.setTitle("PuppetFTP - Manage Your Server - List");
    page.body()->addWidget(_notify);

    // Breadcrumbs
    UI::Title* title = new UI::Title();
    {
        UI::Breadcrumb* link = new UI::Breadcrumb();
        link->addLink("Manage your server", Helper::gen_url("index"));
        link->addLink("Server management", "");
        title->addWidget(link);
    }
    page.body()->addWidget(title);

    // Content
    UI::Container* divContent = new UI::Container();
    {
        divContent->setId("server");

        // Icon
        UI::Container* divIcon = new UI::Container();
        {
            divIcon->addClass("icon users");
            UI::Image* imgContent = new UI::Image("/images/icon_ftp.png", "Manage Your Server");
            imgContent->setAttribute("width", "60");
            divIcon->addWidget(imgContent);
        }
        divContent->addWidget(divIcon);

        // Menu
        UI::Menu* menu = new UI::Menu(UI::Container::NAV);
        {
            menu->setAttribute("id", "menu");
            menu->addMenu("menu", new UI::Link(Helper::gen_url("serverUserList", param), new UI::Text("User management")));
            menu->addMenu("menu", new UI::Link(Helper::gen_url("serverList", param), new UI::Text("Server management")));
        }
        divContent->addWidget(menu);

        // Editing
        divContent->addWidget(_table->getContent());

        // Clear
        UI::Container* divClear = new UI::Container();
        divClear->setAttribute("style", "clear:both;visibility:hidden;");
        divContent->addWidget(divClear);
    }
    page.body()->addWidget(divContent);
    return page.render();
}
