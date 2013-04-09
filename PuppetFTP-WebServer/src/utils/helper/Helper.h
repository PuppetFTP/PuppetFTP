/*
 * Helper.h
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <QString>
#include <QMap>
#include <QVariant>
#include "Route.h"

namespace Helper {

/**
 * This function transform an input string into a slug:
 * Example:
 *   "Hello World !!! I love Bounty !" => "hello-world-i_love-bounty"
 */
QString slugify(const QString& input);
QString formatQdateTime(const QVariant& date);
QString formatEnumProtocol(const QVariant& value);

/**
 * These 2 functions generate an url string corresponding to the given Route.
 * A route may contain some variable which are passed to these function in a map.
 * Example:
 *   For a route named "consult_article" and attached to the url pattern
 *   /article/:id/:title with id the id of the requested article and title the title
 *   of the requested article. Calling one of these helper for an article with id = 12
 *   and title = "Bounty is life !" will produce the following url:
 *     /article/12/bounty-is-life
 */
QString gen_url(const QString& routename, const QMap<QString, QVariant>& parameters = QMap<QString, QVariant>());
QString gen_url(const Routing::Route& route, const QMap<QString, QVariant>& parameters = QMap<QString, QVariant>());

} // namespace Helper

#endif // HELPER_H_
