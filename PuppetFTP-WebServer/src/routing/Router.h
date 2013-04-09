/*
 * Router.h
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#ifndef ROUTER_H_
#define ROUTER_H_

#include <QString>
#include <QHash>
#include "Route.h"

namespace Routing {

class Router {
private:
    static Router*        _instance;

    QHash<QString, Route*> _routing;

    Router();
    virtual ~Router();

public:
    static Router* instance();
    static void    destroy();

    bool   loadRoutes();
    void   addRoute(Route* route);
    Route* getRouteByName(const QString& name) const;
    Route* getRouteByURI(const QString& uri) const;
};

} // namespace Routing

#endif /* ROUTER_H_ */
