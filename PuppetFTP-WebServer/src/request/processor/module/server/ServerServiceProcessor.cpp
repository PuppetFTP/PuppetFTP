#include "ServerServiceProcessor.h"
#include "SessionManager.h"
#include "Session.h"
#include "CommunicationException.h"
#include "EmptyPageRenderer.h"
#include "DatabaseManager.h"
#include "ITable.h"
#include "Helper.h"
#include "Widget.h"
#include "Server.h"
#include "IServerConfigurationProvider.h"
#include "CommunicationService.h"
#include "RuntimeException.h"
#include "Translate.h"

ServerServiceProcessor::ServerServiceProcessor() : AbstractRequestProcessor() {
}

ServerServiceProcessor::~ServerServiceProcessor() {
}

void ServerServiceProcessor::process(HTTPRequest& request) {
    Session* s = SessionManager::instance()->getSession(request.getSessionId());
    bool   err = true;
    _close     = false;
    QString message;

    _id   = request.getParameter("id").toInt();
    _name = request.getParameter("name").toString();
    QMap<QString, QVariant> param;
    param["id"] = _id;

    if (!request.getParameter("submit").isNull()) {
        try {
            Model::Server* server = dynamic_cast<Model::Server*>(DatabaseManager::instance()->getTable("server")->get("id", _id));
            if (server == NULL) {
                message = "ServerConfiguration id " + QString::number(_id) + " doesn't exists.";
            } else {
                // Get a client for the previously added handler...
                IServerConfigurationProvider* client = CommunicationService::provider()->getServiceClient(server->getCorbaId());
                if (client == NULL) {
                    message = "ClientProvider '" + server->getCorbaId() + "' doesn't exists.";
                } else {

                    if (_name == "start") {
                        client->start();
                    } else if (_name == "stop") {
                        client->stop();
                    } else if (_name == "restart") {
                        client->restart();
                    } else {
                        throw new RuntimeException("Service '"+_name+"' unknown.");
                    }
                    err     = false;
                    message = "Server " + server->getName() + ": "+ _name;
                    delete client;
                }
                delete server;
            }
        } catch (const RuntimeException& e) {
            addNotify("Error: '" + e.message(), UI::Notify::ERROR);
            return;
        } catch (const CommunicationException& e) {
            message = "Communication Error: '" + e.message();
        } catch (...) {
            message = "Internal Fatal Error.";
        }
        s->setNotification("service", message, (err ? UI::Notify::ERROR : UI::Notify::INFO));
    }

    if (!request.getParameter("cancel").isNull() || !request.getParameter("submit").isNull()) {
        _close = true;
    }
}

QByteArray ServerServiceProcessor::render() const {
    UI::EmptyPageRenderer page;

    if (_close == false) {
        QMap<QString, QVariant> param;
        param["id"] = _id;

        page.body()->addWidget(_notify);

        Translate::instance()->group("server_service");
        page.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));

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
                    form->addSection("serviceForm", Translate::instance()->tr("message", _name));

                    // Submit
                    UI::Input* submit = new UI::Input("submit", UI::Input::SUBMIT);
                    submit->setValue(Translate::instance()->tr("button_submit"));
                    submit->addClass("btn");
                    form->addWidget("serviceForm", submit);

                    // Cancel
                    UI::Input* cancel = new UI::Input("cancel", UI::Input::SUBMIT);
                    cancel->setValue(Translate::instance()->tr("button_cancel"));
                    cancel->addClass("btn");
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
    } else {
        page.addJavascript("/js/close-sbx.js");
    }
    return page.render();
}
