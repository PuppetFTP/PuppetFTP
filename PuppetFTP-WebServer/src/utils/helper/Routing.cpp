/*
 * Helper.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#include <QStringList>
#include "Helper.h"
#include "Router.h"
#include "RuntimeException.h"

namespace Helper {

QString gen_url(const QString& routename, const QMap<QString, QVariant>& parameters) {
    Routing::Route* route = Routing::Router::instance()->getRouteByName(routename);
    if (route == 0) {
        throw RuntimeException("No route named " + routename);
    }
    return gen_url(*route, parameters);
}

QString gen_url(const Routing::Route& route, const QMap<QString, QVariant>& parameters) {
    QMap<QString, QString> requirements = route.getRequirements();
    QString                uri          = route.getUri();

    // Get argument from URI
    QStringList tmp = uri.split('/');
    QStringList uriArgs;
    for (QStringList::iterator it = tmp.begin(); it != tmp.end(); it++) {
        if ((*it).startsWith(':')) {
            uriArgs << (*it).replace(':', "");
        }
    }
    if (uriArgs.size() == 0) {
        // If no arguments, return the uri
        return uri;
    }

    // Check if all required attributes are given and are correct...
    QStringList missing;
    QStringList invalid;
    for (QStringList::iterator it = uriArgs.begin(); it != uriArgs.end(); it++) {
        if (parameters.contains(*it) == false) {
            missing << *it;
        }
        else {
            if (requirements.contains(*it) && QRegExp(requirements[*it]).exactMatch(parameters[*it].toString()) == false) {
                invalid << *it;
            }
        }
    }
    if (missing.size() > 0) {
        QString message = "Route " + route.getName() + " has some missing parameters:";
        for (QStringList::iterator it = missing.begin(); it != missing.end(); it++) {
            message += " " + *it;
        }
        throw RuntimeException(message);
    }
    if (invalid.size() > 0) {
        QString message = "Route " + route.getName() + " has some invalid parameters:";
        for (QStringList::iterator it = invalid.begin(); it != invalid.end(); it++) {
            message += " " + *it;
        }
        throw RuntimeException(message);
    }

    // Generate the url
    for (QMap<QString, QVariant>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
        QString arg = it.value().toString();
        if (it.value().type() == QVariant::String) {
            arg = slugify(arg);
        }
        uri = uri.replace(":" + it.key(), arg);
    }

    return uri;
}

} // namespace Helper
