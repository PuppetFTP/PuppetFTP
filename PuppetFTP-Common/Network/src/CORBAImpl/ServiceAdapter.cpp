/*
 * ServiceAdapter.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include "ServiceAdapter.h"

namespace CORBA {
namespace Impl {

ServiceAdapter::ServiceAdapter() {
}

ServiceAdapter::ServiceAdapter(IServerConfigurationProvider* provider) : _configurator(provider) {
}

ServiceAdapter::~ServiceAdapter() {
    delete _configurator;
}

// Network
char* ServiceAdapter::getServerName() {
    std::string name = _configurator->getServerName().toStdString();
    char* tmp = new char[name.size() + 1];
    std::copy(name.begin(), name.end(), tmp);
    tmp[name.size()] = 0;
    return tmp;
}

void ServiceAdapter::setServerName(const char* name) {
    _configurator->setServerName(QString(name));
}

char* ServiceAdapter::getServerAddr() {
    std::string addr = _configurator->getServerAddr().toStdString();
    char* tmp = new char[addr.size() + 1];
    std::copy(addr.begin(), addr.end(), tmp);
    tmp[addr.size()] = 0;
    return tmp;
}

unsigned short ServiceAdapter::getServerPort() {
    return _configurator->getServerPort();
}

void ServiceAdapter::setServerPort(unsigned short port) {
    _configurator->setServerPort(port);
}

ServerConfigHandler::INTERNET_PROTOCOL ServiceAdapter::getInternetProtocol() {
    IServerConfigurationProvider::INTERNET_PROTOCOL::ip ip = _configurator->getInternetProtocol();
    if (ip == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4)
        return ServerConfigHandler::IPv4;
    else if (ip == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv6)
        return ServerConfigHandler::IPv6;
    return ServerConfigHandler::undefined;
}

void ServiceAdapter::setInternetProtocol(ServerConfigHandler::INTERNET_PROTOCOL ip) {
    if (ip == ServerConfigHandler::IPv4)
        _configurator->setInternetProtocol(IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4);
    else if (ip == ServerConfigHandler::IPv6)
        _configurator->setInternetProtocol(IServerConfigurationProvider::INTERNET_PROTOCOL::IPv6);
    else
        _configurator->setInternetProtocol(IServerConfigurationProvider::INTERNET_PROTOCOL::undefined);
}

unsigned short ServiceAdapter::getIdleTimeout() {
    return _configurator->getIdleTimeout();
}

void ServiceAdapter::setIdleTimeout(unsigned short timeout) {
    _configurator->setIdleTimeout(timeout);
}

unsigned short ServiceAdapter::getDataConnectionTimeout() {
    return _configurator->getDataConnectionTimeout();
}

void ServiceAdapter::setDataConnectionTimeout(unsigned short timeout) {
    _configurator->setDataConnectionTimeout(timeout);
}

// User
bool ServiceAdapter::isUsingSystemUser() {
    return _configurator->isUsingSystemUser();
}

void ServiceAdapter::useSystemUser(bool use) {
    _configurator->useSystemUser(use);
}

bool ServiceAdapter::isAnonymousAllowed() {
    return _configurator->isAnonymousAllowed();
}

void ServiceAdapter::allowAnonymous(bool allow) {
    _configurator->allowAnonymous(allow);
}

bool ServiceAdapter::isAnonymousUploadAllowed() {
    return _configurator->isAnonymousUploadAllowed();
}

void ServiceAdapter::allowAnonymousUpload(bool allow) {
    _configurator->allowAnonymous(allow);
}

bool ServiceAdapter::isAnonymousCreateDirAllowed() {
    return _configurator->isAnonymousCreateDirAllowed();
}

void ServiceAdapter::allowAnonymousCreateDir(bool allow) {
    _configurator->allowAnonymousCreateDir(allow);
}

ServerConfigHandler::VIRTUAL_USER_AUTHENTICATION ServiceAdapter::getVirtualUserAuthentication() {
    return ServerConfigHandler::Anonymous;
}

void ServiceAdapter::setVirtualUserAuthentication(ServerConfigHandler::VIRTUAL_USER_AUTHENTICATION mode) {
    _configurator->setVirtualUserAuthentication(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::Anonymous);
}

void ServiceAdapter::addVirtualUser(const char* user, const char* password) {
    _configurator->addVirtualUser(QString(user), QString(password));
}

void ServiceAdapter::remVirtualUser(const char* user) {
    _configurator->remVirtualUser(QString(user));
}

ServerConfigHandler::StringSequence* ServiceAdapter::virtualUsers() {
    QStringList list = _configurator->virtualUsers();
    ServerConfigHandler::StringSequence* out = new ServerConfigHandler::StringSequence();
    out->length(list.size());
    int i = 0;
    for (QStringList::iterator it = list.begin(); it != list.end(); it++, i++) {
        (*out)[i] = (*it).toStdString().c_str();
    }
    return out;
}

// Misc
char* ServiceAdapter::getWelcomeMessage() {
    std::string file = _configurator->getWelcomeMessage().toStdString();
    char* tmp = new char[file.size() + 1];
    std::copy(file.begin(), file.end(), tmp);
    tmp[file.size()] = 0;
    return tmp;
}

void  ServiceAdapter::setWelcomeMessage(const char* message) {
    _configurator->setWelcomeMessage(QString(message));
}

char* ServiceAdapter::getLogFile() {
    std::string file = _configurator->getLogFile().toStdString();
    char* tmp = new char[file.size() + 1];
    std::copy(file.begin(), file.end(), tmp);
    tmp[file.size()] = 0;
    return tmp;
}

// import/export
void ServiceAdapter::importConfiguration(const char* configuration) {
    _configurator->importConfiguration(configuration);
}

char* ServiceAdapter::exportConfiguration() {
    std::string conf = _configurator->exportConfiguration().toStdString();
    char* tmp = new char[conf.size() + 1];
    std::copy(conf.begin(), conf.end(), tmp);
    tmp[conf.size()] = 0;
    return tmp;
}

void ServiceAdapter::resetConfiguration() {
    _configurator->resetConfiguration();
}

// Start/stop
void ServiceAdapter::start() {
    _configurator->start();
}

void ServiceAdapter::stop() {
    _configurator->stop();
}

void ServiceAdapter::restart() {
    _configurator->restart();
}

} // Impl
} // CORBA

