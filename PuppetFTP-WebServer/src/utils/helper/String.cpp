/*
 * String.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#include <QString>
#include <QRegExp>
#include <QDateTime>
#include "Helper.h"
#include "IServerConfigurationProvider.h"

namespace Helper {

QString slugify(const QString& input) {
    return input.toLower().replace(QRegExp("[^\\d\\w]+"), "-")
                          .replace(QRegExp("^-+|-+$"), "");
}

QString formatQdateTime(const QVariant& date) {
    return date.toDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

QString formatEnumProtocol(const QVariant& val) {
    return QString::number(val.value< IServerConfigurationProvider::INTERNET_PROTOCOL::ip >());
}


} // namespace Helper
