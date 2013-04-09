/*
 * ServerConfWrapper.cpp
 *
 *  Created on: 6 janv. 2013
 *      Author: laplace
 */

#include "ServerConfWrapper.h"

namespace UI {

ServerConfWrapper::ServerConfWrapper(IServerConfigurationProvider* provider) : _provider(provider) {
}

ServerConfWrapper::~ServerConfWrapper() {
}

QString ServerConfWrapper::getServerName() const {
    return _provider->getServerName();
}

QString ServerConfWrapper::getServerAddr() const {
    return _provider->getServerAddr();
}

quint16 ServerConfWrapper::getServerPort() const {
    return _provider->getServerPort();
}

IServerConfigurationProvider::INTERNET_PROTOCOL::ip ServerConfWrapper::getInternetProtocol() const {
    return _provider->getInternetProtocol();
}

quint16 ServerConfWrapper::getIdleTimeout() const {
    return _provider->getIdleTimeout();
}

quint16 ServerConfWrapper::getDataConnectionTimeout() const {
    return _provider->getDataConnectionTimeout();
}

bool ServerConfWrapper::isUsingSystemUser() const {
    return _provider->isUsingSystemUser();
}

bool ServerConfWrapper::isAnonymousAllowed() const {
    return _provider->isAnonymousAllowed();
}

bool ServerConfWrapper::isAnonymousUploadAllowed() const {
    return _provider->isAnonymousUploadAllowed();
}

bool ServerConfWrapper::isAnonymousCreateDirAllowed() const {
    return _provider->isAnonymousCreateDirAllowed();
}

IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth ServerConfWrapper::getVirtualUserAuthentication() const {
    return _provider->getVirtualUserAuthentication();
}

QStringList ServerConfWrapper::virtualUsers() const {
    return _provider->virtualUsers();
}

QString ServerConfWrapper::getWelcomeMessage() const {
    return _provider->getWelcomeMessage();
}

QString ServerConfWrapper::getLogFile() const {
    return _provider->getLogFile();
}

} // namespace UI
