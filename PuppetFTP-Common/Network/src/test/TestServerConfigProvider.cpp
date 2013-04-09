/*
 * TestServerConfigProvider.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include <QDebug>
#include "TestServerConfigProvider.h"

TestServerConfigProvider::TestServerConfigProvider() :
    _name(TEST_SERVER_NAME), _port(123),
    _ip(INTERNET_PROTOCOL::IPv4), _idleTimeout(30), _dataTimeout(60), _useSystemUser(true),
    _anonymousAllowed(true), _anonymousUpload(false), _anonymousCreateDir(false),
    _bannedList("/lorem/ipsum/dolor.si"), _welcomeMessage("Hello World !!!") {
}

TestServerConfigProvider::~TestServerConfigProvider() {
}

QString TestServerConfigProvider::getServerName() const {
    return _name;
}

void TestServerConfigProvider::setServerName(const QString& name) {
    _name = name;
}

QString TestServerConfigProvider::getServerAddr() const {
    return "127.0.0.1";
}

quint16 TestServerConfigProvider::getServerPort() const {
    return _port;
}

void TestServerConfigProvider::setServerPort(quint16 port) {
    _port = port;
}

IServerConfigurationProvider::INTERNET_PROTOCOL::ip TestServerConfigProvider::getInternetProtocol() const {
    return IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4;
}

void TestServerConfigProvider::setInternetProtocol(IServerConfigurationProvider::INTERNET_PROTOCOL::ip ip) {
    _ip = ip;
}

quint16 TestServerConfigProvider::getIdleTimeout() const {
    return _idleTimeout;
}

void TestServerConfigProvider::setIdleTimeout(quint16 timeout) {
    _idleTimeout = timeout;
}

quint16 TestServerConfigProvider::getDataConnectionTimeout() const {
    return _dataTimeout;
}

void TestServerConfigProvider::setDataConnectionTimeout(quint16 timeout) {
    _dataTimeout = timeout;
}

bool TestServerConfigProvider::isUsingSystemUser() const {
    return _useSystemUser;
}

void TestServerConfigProvider::useSystemUser(bool use) {
    _useSystemUser = use;
}

bool TestServerConfigProvider::isAnonymousAllowed() const {
    return _anonymousAllowed;
}

void TestServerConfigProvider::allowAnonymous(bool allow) {
    _anonymousAllowed = allow;
}

bool TestServerConfigProvider::isAnonymousUploadAllowed() const {
    return _anonymousUpload;
}

void TestServerConfigProvider::allowAnonymousUpload(bool allow) {
    _anonymousUpload = allow;
}

bool TestServerConfigProvider::isAnonymousCreateDirAllowed() const {
    return _anonymousCreateDir;
}

void TestServerConfigProvider::allowAnonymousCreateDir(bool allow) {
    _anonymousCreateDir = allow;
}

IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth TestServerConfigProvider::getVirtualUserAuthentication() const {
    return IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::Anonymous;
}

void TestServerConfigProvider::setVirtualUserAuthentication(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth mode) {
}

void TestServerConfigProvider::addVirtualUser(const QString& user, const QString& password) {
}

void TestServerConfigProvider::remVirtualUser(const QString& user) {
}

QStringList TestServerConfigProvider::virtualUsers() const {
    QStringList list;
    list << "Lorem"
         << "ipsum"
         << "dolor"
         << "si"
         << "amet";
    return list;
}

QString TestServerConfigProvider::getWelcomeMessage() const {
    return _welcomeMessage;
}

void TestServerConfigProvider::setWelcomeMessage(const QString& message) {
    _welcomeMessage = message;
}

QString TestServerConfigProvider::getLogFile() const {
    return "/var/log/test_server.log";
}

void TestServerConfigProvider::importConfiguration(const QString& configuration) {
}

QString TestServerConfigProvider::exportConfiguration() const {
    return "";
}

void TestServerConfigProvider::resetConfiguration() {
}

void TestServerConfigProvider::start() const {
    qDebug() << "Start server...";
}

void TestServerConfigProvider::stop() const {
    qDebug() << "Stop server...";
}

void TestServerConfigProvider::restart() const {
    qDebug() << "Restart server...";
}
