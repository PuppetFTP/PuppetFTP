#include "ServerServiceProcessor.h"
#include "SessionManager.h"
#include "Session.h"
#include "CommunicationException.h"
#include "DefaultPageRenderer.h"
#include "DatabaseManager.h"
#include "ITable.h"
#include "Helper.h"
#include "Widget.h"
#include "Server.h"
#include "IServerConfigurationProvider.h"
#include "CommunicationService.h"
#include "RuntimeException.h"

ServerServiceProcessor::ServerServiceProcessor() : AbstractRequestProcessor() {
}

ServerServiceProcessor::~ServerServiceProcessor() {
}

QStringList ServerServiceProcessor::getRequiredCrendentials() const {
    QStringList list;
    return list;
}

void ServerServiceProcessor::process(HTTPRequest& request) {
    Session* s = SessionManager::instance()->getSession(request.getSessionId());

    _id   = request.getParameter("id").toInt();
    _name = request.getParameter("name").toString();
    QMap<QString, QVariant> param;
    param["id"] = _id;

    if (!request.getParameter("submit").isNull()) {
        try {
            Model::Server* server = dynamic_cast<Model::Server*>(DatabaseManager::instance()->getTable("server")->get("id", _id));
            if (server == NULL) {
                s->setNotification("service", "ServerConfiguration id " + QString::number(_id) + " doesn't exists.", UI::Notify::ERROR);
                request.redirect(Helper::gen_url("serverEdit", param));
                return;
            }
            // Get a client for the previously added handler...
            IServerConfigurationProvider* client = CommunicationService::provider()->getServiceClient(server->getCorbaId());
            if (client == NULL) {
                s->setNotification("service", "ClientProvider '" + server->getCorbaId() + "' doesn't exists.", UI::Notify::ERROR);
                request.redirect(Helper::gen_url("serverEdit", param));
                delete server;
                return;
            }
            if (_name == "start") {
                client->start();
            } else if (_name == "stop") {
                client->stop();
            } else if (_name == "restart") {
                client->restart();
            } else {
                throw new RuntimeException("Service '"+_name+"' unknown.");
            }
            request.redirect(Helper::gen_url("serverEdit", param));
            s->setNotification("service", "Server " + server->getName() + ": "+ _name, UI::Notify::INFO);

            delete server;
            delete client;
        } catch (const RuntimeException& e) {
            addNotify("Error: '" + e.message(), UI::Notify::ERROR);
        } catch (const CommunicationException& e) {
            s->setNotification("service", "Communication Error: '" + e.message(), UI::Notify::ERROR);
            request.redirect(Helper::gen_url("serverEdit", param));
        } catch (...) {
            s->setNotification("service", "Internal Fatal Error.", UI::Notify::ERROR);
            request.redirect(Helper::gen_url("serverEdit", param));
        }
    } else if (!request.getParameter("cancel").isNull()) {
        request.redirect(Helper::gen_url("serverEdit", param));
    }
}

QByteArray ServerServiceProcessor::render() const {
    UI::DefaultPageRenderer page;
    QMap<QString, QVariant> param;
    param["id"] = _id;

    page.setTitle("PuppetFTP - Configure");
    page.body()->addWidget(_notify);

    // Breadcrumbs
    UI::Title* title = new UI::Title();
    {
        UI::Breadcrumb* link = new UI::Breadcrumb();
        link->addLink("Manage your server", Helper::gen_url("index"));
        link->addLink("Server management", Helper::gen_url("serverEdit", param));
        link->addLink("Service management", "");
        title->addWidget(link);
    }
    page.body()->addWidget(title);


    // Content
    UI::Container* divContent = new UI::Container(UI::Container::SECTION);
    {
        divContent->setId("action");
        // Service
        UI::Container* div = new UI::Container();
        {
            div->addClass("box");
            // Create Form
            param["name"] = _name;
            UI::Form* form = new UI::Form(Helper::gen_url("serverService", param));
            {
                form->setRendering(UI::Form::NONE);
                form->setRendererLabel(false);
                form->setId("serviceForm");
                form->setAttribute("novalidate", "novalidate");
                form->addSection("serviceForm", "Are you sure to " + _name + " the server ?");

                // Submit
                UI::Input* submit = new UI::Input("submit", UI::Input::SUBMIT);
                submit->setValue("Yes");
                submit->addClass("yes");
                form->addWidget("serviceForm", submit);

                // Cancel
                UI::Input* cancel = new UI::Input("cancel", UI::Input::SUBMIT);
                cancel->setValue("Cancel");
                cancel->addClass("cancel");
                form->addWidget("serviceForm", cancel);
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

    return page.render();
}
