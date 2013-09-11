/*
 * TestServerConfigProvider.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include <QDebug>
#include <QVariantHash>
#include "TestServerConfigProvider.h"

TestServerConfigProvider::TestServerConfigProvider() :
    _name(TEST_SERVER_NAME) {
}

TestServerConfigProvider::~TestServerConfigProvider() {
}

bool TestServerConfigProvider::loadPlugin(const QString & pluginId, const QString & pluginName) {
	qDebug() << "loadPlugin:: pluginId: " << pluginId << "pluginName:" << pluginName;
	return true;
}

bool TestServerConfigProvider::unloadPlugin(const QString & pluginId) {
	qDebug() << "unloadPlugin:: pluginId:" << pluginId;
	return true;
}

bool TestServerConfigProvider::set(const QString & pluginId, const QString & propertyName, const QVariant & value) {
	qDebug() << "set:: pluginId:" << pluginId << "propertyName:" << propertyName << "value:" << value;
	return true;
}

QVariant TestServerConfigProvider::get(const QString & pluginId, const QString & propertyName) {
	qDebug() << "get:: pluginId:" << pluginId << "propertyName:" << propertyName;
	return QVariant(QString("Hello World !!!"));
}

QVariant TestServerConfigProvider::exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList) {
	qDebug() << "exec:: pluginId:" << pluginId << "taskName:" << taskName << "argumentList:" << argumentList;
	return QVariant(QString("EXEC_DONE"));
}

QStringList TestServerConfigProvider::metaProperties(const QString & pluginId) {
	qDebug() << "metaProperties:: pluginId:" << pluginId;
	QStringList sl;
	sl << "Hello" << "World" << "!!!";
	return sl;
}

QStringList TestServerConfigProvider::metaTasks(const QString & pluginId) {
	qDebug() << "metaTasks:: pluginId:" << pluginId;
	QStringList sl;
	sl << "Hello" << "World" << "!!!";
	return sl;
}

QString TestServerConfigProvider::lastErrorString() {
	qDebug() << "lastErrorString::";
	return QString("NO ERROR");
}

bool TestServerConfigProvider::hasFailure() {
	qDebug() << "hasFailure::";
	return false;
}
