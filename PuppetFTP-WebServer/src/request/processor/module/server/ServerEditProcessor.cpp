#include <QMetaProperty>
#include <exception>
#include "ServerEditProcessor.h"
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

ServerEditProcessor::ServerEditProcessor() : AbstractRequestProcessor() {
}

ServerEditProcessor::~ServerEditProcessor() {
}

QStringList ServerEditProcessor::getRequiredCredentials() const {
    QStringList list;
    return list;
}

void ServerEditProcessor::process(HTTPRequest& request) {
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
    _form->getForm()->setAction(Helper::gen_url("serverEdit", param));

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

QByteArray ServerEditProcessor::render() const {
    UI::DefaultPageRenderer page;
    QMap<QString, QVariant> param;

    page.setTitle("PuppetFTP - Manage Your Server");
    page.body()->addWidget(_notify);

    // Breadcrumbs
    UI::Title* title = new UI::Title();
    {
        title->addClass("editServer");
        UI::Breadcrumb* link = new UI::Breadcrumb();
        link->addLink("Manage your server", Helper::gen_url("index"));
        link->addLink("Server management", "");
        title->addWidget(link);
    }
    page.body()->addWidget(title);

    // Add button
    UI::Container* buttons = new UI::Container();
    {
        buttons->addClass("buttons");
        param["id"] = _id;
        param["name"] = "start";
        UI::Link* linkStart = new UI::Link(Helper::gen_url("serverService", param), new UI::Text("Start"));
        linkStart->addClass("button");
        buttons->addWidget(linkStart);

        param["name"] = "stop";
        UI::Link* linkStop = new UI::Link(Helper::gen_url("serverService", param), new UI::Text("Stop"));
        linkStop->addClass("button");
        buttons->addWidget(linkStop);

        param["name"] = "restart";
        UI::Link* linkRetart = new UI::Link(Helper::gen_url("serverService", param), new UI::Text("Restart"));
        linkRetart->addClass("button");
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
        divContent->addWidget(_form->getContent());

        // Clear
        UI::Container* divClear = new UI::Container();
        divClear->setAttribute("style", "clear:both;visibility:hidden;");
        divContent->addWidget(divClear);
    }
    page.body()->addWidget(divContent);
    return page.render();
}
