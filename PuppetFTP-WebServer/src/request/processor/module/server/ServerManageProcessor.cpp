#include <QMetaProperty>
#include <exception>
#include "ServerManageProcessor.h"
#include "DefaultPageRenderer.h"
#include "CORBAImpl/Provider.h"
#include "CommunicationService.h"
#include "IServerConfigurationProvider.h"
#include "RuntimeException.h"
#include "processor/AbstractRequestProcessor.h"
#include "ModelWidgetFactory.h"
#include "ServerConfWrapper.h"
#include "DatabaseManager.h"
#include "Widget.h"
#include "Helper.h"
#include "ITable.h"
#include "Server.h"
#include "Session.h"
#include "SessionManager.h"
#include "CommunicationException.h"
#include "Translate.h"

ServerManageProcessor::ServerManageProcessor() : AbstractRequestProcessor() {
}

ServerManageProcessor::~ServerManageProcessor() {
}

QStringList ServerManageProcessor::getRequiredCrendentials() const {
    QStringList list;
    return list;
}

void ServerManageProcessor::process(HTTPRequest& request) {
    _id        = request.getParameter("id").toInt();
    Session* s = SessionManager::instance()->getSession(request.getSessionId());
    addNotify(s->getNotification("edit"));
    addNotify(s->getNotification("service"));

    QMap<QString, QVariant> param;
    param.insert("id", _id);

    _form = UI::ModelWidgetFactory::instance()->getEditorWidget("serverConfigurationEditor");
    if (_form == NULL){
        s->setNotification("edit", "Model Form Entity 'serverConfiguration' doesn't exists.", UI::Notify::ERROR);
        request.redirect(Helper::gen_url("serverList", param));
        return;
    }
    _form->getForm()->setAction(Helper::gen_url("serverManage", param));

    try {
        Model::Server* server = dynamic_cast<Model::Server*>(DatabaseManager::instance()->getTable("server")->get("id", _id));
        if (server == NULL) {
            s->setNotification("edit", "ServerConfiguration id " + QString::number(_id) + " doesn't exists.", UI::Notify::ERROR);
            request.redirect(Helper::gen_url("serverList", param));
            return;
        }
        // Get a client for the previously added handler...
        IServerConfigurationProvider* client = CommunicationService::provider()->getServiceClient(server->getCorbaId());
        if (client == NULL) {
            addNotify("ClientProvider '" + server->getCorbaId() + "' doesn't exists.", UI::Notify::ERROR);
            return;
        }
        if (!request.getParameter("submit").isNull()) {
//            client->setServerName(request.getParameter("server_name").toString());
            client->setServerPort(request.getParameter("server_port").toUInt());
            client->setInternetProtocol((IServerConfigurationProvider::INTERNET_PROTOCOL::ip)request.getParameter("internet_protocol").toInt());
            client->setIdleTimeout(request.getParameter("idle_timeout").toUInt());
            client->setDataConnectionTimeout(request.getParameter("data_timeout").toUInt());
            //client->useSystemUser(request.getParameter("use_system_user").toBool());
            //client->allowAnonymous(request.getParameter("anonymous_allowed").toInt());
            //client->allowAnonymousUpload(request.getParameter("anonymous_upload_allowed"));
            //client->allowAnonymousCreateDir(request.getParameter("anonymouse_create_dir_allowed"));
            //client->setVirtualUserAuthentication(request.getParameter("virtual_user_auth"));
            client->setWelcomeMessage(request.getParameter("welcome_message").toString());
            addNotify("Update success.", UI::Notify::INFO);
        }
        QObject* object = new UI::ServerConfWrapper(client);
        if (object == NULL) {
            addNotify("Server configuration '" + server->getCorbaId() + "' cannot be load.", UI::Notify::ERROR);
            return;
        }
        _form->bind(object);

        delete object;
        delete server;
        delete client;
    } catch (const RuntimeException& e) {
        addNotify("Internal Runtime Error: '" + e.message()+".", UI::Notify::ERROR);
    } catch (const CommunicationException& e) {
        addNotify("Communication Error: '" + e.message()+".", UI::Notify::ERROR);
    } catch (...) {
        addNotify("Internal Fatal Error.", UI::Notify::ERROR);
    }
}

QByteArray ServerManageProcessor::render() const {
    UI::DefaultPageRenderer page;
    QMap<QString, QVariant> param;

    page.body()->addWidget(_notify);

    Translate::instance()->group("breadcrumb");
    // Breadcrumbs
    UI::Title* title = new UI::Title();
    {
        title->addClass("editServer");
        UI::Breadcrumb* link = new UI::Breadcrumb();
        link->addLink(Translate::instance()->tr("server_home"), Helper::gen_url("index"));
        link->addLink(Translate::instance()->tr("server_manage"), Helper::gen_url("serverList"));
        link->addLink(Translate::instance()->tr("server_config"), "");
        title->addWidget(link);
    }
    page.body()->addWidget(title);

    Translate::instance()->group("server_manage");
    page.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));

    // Add button
    UI::Container* buttons = new UI::Container();
    buttons->addClass("btn-group");
    {
        buttons->addClass("buttons");
        param["id"] = _id;
        param["name"] = "start";
        UI::Link* linkStart = new UI::Link(Helper::gen_url("serverService", param), new UI::Text(Translate::instance()->tr("button_start")));
        linkStart->addClass("btn");
        linkStart->setAttribute("rel", "shadowbox; width=500;height=110");
        buttons->addWidget(linkStart);

        param["name"] = "stop";
        UI::Link* linkStop = new UI::Link(Helper::gen_url("serverService", param), new UI::Text(Translate::instance()->tr("button_stop")));
        linkStop->addClass("btn");
        linkStop->setAttribute("rel", "shadowbox; width=500;height=110");
        buttons->addWidget(linkStop);

        param["name"] = "restart";
        UI::Link* linkRetart = new UI::Link(Helper::gen_url("serverService", param), new UI::Text(Translate::instance()->tr("button_restart")));
        linkRetart->addClass("btn");
        linkRetart->setAttribute("rel", "shadowbox; width=500;height=110");
        buttons->addWidget(linkRetart);
    }
    page.body()->addWidget(buttons);

    // Content
    UI::Container* divContent = new UI::Container();
    {
        divContent->setId("server");

        // Icon
        UI::Container* divIcon = new UI::Container();
        {
            divIcon->addClass("icon users");
            UI::Image* imgContent = new UI::Image("/img/icon_ftp.png", Translate::instance()->tr("icon"));
            imgContent->setAttribute("width", "60");
            divIcon->addWidget(imgContent);
        }
        divContent->addWidget(divIcon);

        // Menu
        UI::Menu* menu = new UI::Menu(UI::Container::NAV);
        {
            menu->setAttribute("id", "menu");
            menu->addMenu("menu", new UI::Link(Helper::gen_url("serverUserList"), new UI::Text(Translate::instance()->tr("menu_user"))));
            menu->addMenu("menu", new UI::Link(Helper::gen_url("serverList"), new UI::Text(Translate::instance()->tr("menu_server"))));
        }
        divContent->addWidget(menu);

        // Editing
        divContent->addWidget(_form->getContent());

        // Clear
        UI::Container* divClear = new UI::Container();
        divClear->setAttribute("style", "clear:both;visibility:hidden;");
        divContent->addWidget(divClear);
    }
    page.body()->addWidget(divContent);
    return page.render();
}
