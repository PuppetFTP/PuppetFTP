/*
 * Router.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#include "Router.h"
#include "RouteReader.h"
#include "ParsingException.h"

namespace Routing {

Router* Router::_instance = 0;

Router::Router() {
}

Router::~Router() {
    for (QHash<QString, Route*>::iterator it = _routing.begin(); it != _routing.end(); it++) {
        Route* r = it.value();
        if (r != 0) {
            delete r;
        }
    }
}

Router* Router::instance() {
    if (_instance == 0) {
        _instance = new Router();
    }
    return _instance;
}

void Router::destroy() {
    if (_instance != 0) {
        delete _instance;
    }
}

bool Router::loadRoutes() {
    RouteReader reader("config/routing.xml");
    try {
        QList<Routing::Route*> routes = reader.parse();
        for (QList<Routing::Route*>::iterator it = routes.begin(); it != routes.end(); it++) {
            _routing[(*it)->getName()] = *it;
        }
    } catch (const ParsingException& e) {
        qCritical() << e.message();
        return false;
    }
    return true;
}

void Router::addRoute(Route* route) {
    if (_routing.contains(route->getName()) && _routing[route->getName()] != 0) {
        qWarning() << "A request route named" << route->getName() << "already registered, override it";
        delete _routing[route->getName()];
    }
    _routing[route->getName()] = route;
}

Route* Router::getRouteByName(const QString& name) const {
    if (_routing.contains(name))
        return _routing[name];
    return 0;
}

Route* Router::getRouteByURI(const QString& uri) const {
    QList<Route*> routes = _routing.values();
    for (QList<Route*>::iterator it = routes.begin(); it != routes.end(); it++) {
        Route* route    = *it;
        QString pattern = route->getUri();
        QStringList uriArgs = pattern.split('/');
        for (int i = 0; i < uriArgs.size(); i++) {
            if (uriArgs[i].startsWith(':')) {
                try {
                    pattern = pattern.replace(uriArgs[i], route->getRequirement(uriArgs[i].split(':').at(1)));
                } catch (...) {
                    // ignore error, pattern will not be replaced
                }
            }
        }
        if (QRegExp(pattern).exactMatch(uri)) {
            return route;
        }
    }
    return 0;
}

} // namespace Routing
