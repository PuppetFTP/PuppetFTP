/*
 * RequestDispatcher.cpp
 *
 *  Created on: 3 oct. 2012
 *      Author: laplace
 */

#include <QDebug>
#include <QDateTime>
#include <QRegExp>
#include <QHash>
#include "RequestDispatcher.h"
#include "Router.h"
#include "RequestProcessorFactory.h"
#include "Session.h"
#include "SessionManager.h"
#include "RuntimeException.h"
#include "DefaultPageRenderer.h"
#include "OutputRendererFactory.h"
#include "Processor.h"


RequestDispatcher* RequestDispatcher::_instance = 0;

RequestDispatcher::RequestDispatcher() {
}

RequestDispatcher::~RequestDispatcher() {
}

RequestDispatcher* RequestDispatcher::instance() {
    if (_instance == 0) {
        _instance = new RequestDispatcher;
    }
    return _instance;
}

void RequestDispatcher::destroy() {
    if (_instance != 0) {
        delete _instance;
    }
}

bool RequestDispatcher::configure() {
    // RequestProcessor
    RequestProcessorFactory::instance()->registerProcessor<ResourceProcessor>("resource");
    RequestProcessorFactory::instance()->registerProcessor<ConnectionProcessor>("login");
    RequestProcessorFactory::instance()->registerProcessor<DisconnectProcessor>("logout");
    RequestProcessorFactory::instance()->registerProcessor<IndexProcessor>("index");
    RequestProcessorFactory::instance()->registerProcessor<IndexProcessor>("lang");

    // Entity
    RequestProcessorFactory::instance()->registerProcessor<EntityListProcessor>("entityList");
    RequestProcessorFactory::instance()->registerProcessor<EntityEditProcessor>("entityAdd");
    RequestProcessorFactory::instance()->registerProcessor<EntityEditProcessor>("entityEdit");
    //RequestProcessorFactory::instance()->registerProcessor<EntityViewProcessor>("entityView");
    RequestProcessorFactory::instance()->registerProcessor<EntityDeleteProcessor>("entityDelete");
    RequestProcessorFactory::instance()->registerProcessor<UnavailableProcessor>("importExport");

    // Server
    RequestProcessorFactory::instance()->registerProcessor<ServerManageProcessor>("serverManage");
    RequestProcessorFactory::instance()->registerProcessor<ServerListProcessor>("serverList");
    RequestProcessorFactory::instance()->registerProcessor<ServerServiceProcessor>("serverService");
    RequestProcessorFactory::instance()->registerProcessor<UnavailableProcessor>("serverUserList");
    return true;
}

HTTPResponse RequestDispatcher::dispatch(HTTPRequest& request) {
    HTTPResponse response;
    try {
        request.parseHeader();
        bool requestIsResource = (request.getRequestedURI() != "/" && QFile::exists("./web/" + request.getRequestedURI()));
        qDebug() << "New request:" << request.getRequestedURI();
        // Look at Session...
        Session* session = SessionManager::instance()->getSession(request.getSessionId(), request.getPeer());
        if (session == 0) {
            qDebug() << "No session can be found, create a new one...";
            session = SessionManager::instance()->newSession(request.getPeer());
            request.setSessionId(session->getId());
            qDebug() << "  SESSID:" << session->getId();
        }
        session->updateAccess();
        response.setCookie("SESSID", session->toCookieString());
        qDebug() << "Current active session:" << session->getId();

        // Get requested route...
        qDebug() << "Requested URI:" << request.getRequestedURI();
        Routing::Route* route = Routing::Router::instance()->getRouteByURI(request.getRequestedURI());

        // Check authentication...
        if (session->isAuthenticated() == false) {
            if ((route == 0 || route->getName() != "login") && requestIsResource == false) {
                qDebug() << "User is not authenticated and request is not the connection route, redirect for connection";
                response.redirect(Routing::Router::instance()->getRouteByName("login")->getUri());
                return response;
            }
        }

        // Treat the request...
        if (route == 0 && requestIsResource == false) {
            qDebug() << "No route can be found for" << request.getRequestedURI();
            response.notFound(request.getRequestedURI());
            return response;
        }
        IRequestProcessor* processor = 0;
        if (requestIsResource == true) {
            qDebug() << "Request is a resource";
            processor = RequestProcessorFactory::instance()->getProcessor("resource");
        }
        else {
            request.parseData(*route);
            processor = RequestProcessorFactory::instance()->getProcessor(route->getProcessor());
        }
        if (processor == 0) {
            qDebug() << "No processor can be found for route" << route->getName() << "(request:" << request.getRequestedURI() << ")";
            response.error("Cannot treat the request: " + request.getRequestedURI());
            return response;
        }
        if (canAccessToProcessor(processor, *session) == false) {
            qDebug() << "Access is not permitted";
            response.forbidden();
            return response;
        }
        processor->process(request);
        if (request.isRedirected() == true) {
            qDebug() << "Request has been redirected to" << request.getRedirection();
            response.redirect(request.getRedirection());
            return response;
        }
        response.setParameter("Content-Type", processor->getContentType());
        if (processor->hasAdditionalHeaderParameters()) {
            QHash<QString, QString> parameters = processor->getAdditionalHeaderParameters();
            for (QHash<QString, QString>::iterator it = parameters.begin(); it != parameters.end(); ++it) {
                response.setParameter(it.key(), it.value());
            }
        }
        response.setContent(processor->render());
        qDebug() << "Response has been treated, response is sent";
        delete processor;
    } catch (const RuntimeException& e) {
        qCritical() << e.message();
        response.error(e.message());
    }
    return response;
}

bool RequestDispatcher::canAccessToProcessor(IRequestProcessor* processor, const Session& session) const {
    QStringList credentials = processor->getRequiredCrendentials();
    if (credentials.size() > 0) {
        for (QStringList::iterator it = credentials.begin(); it != credentials.end(); it++) {
            if (session.hasCredential(*it) == true) {
                return true;
            }
        }
    }
    else {
        return true;
    }
    return false;
}
