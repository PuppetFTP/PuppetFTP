/*
 * ServiceClientAdapter.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include "ServerConfigHandler.hh"
#include "ServiceClientAdapter.h"
#include "CommunicationException.h"

#define ACCESS_ERROR_MESSAGE "Unable to perform operation, please verify your configuration"

namespace CORBA {
namespace Impl {

ServiceClientAdapter::ServiceClientAdapter(const ServerConfigHandler_var& handler) : _handler(handler) {
}

ServiceClientAdapter::~ServiceClientAdapter() {
}

QString ServiceClientAdapter::getServerName() const {
    try {
        return QString(_handler->getServerName());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::setServerName(const QString& name) {
    try {
        _handler->setServerName(name.toStdString().c_str());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

QString ServiceClientAdapter::getServerAddr() const {
    try {
        return QString(_handler->getServerAddr());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

quint16 ServiceClientAdapter::getServerPort() const {
    try {
        return _handler->getServerPort();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::setServerPort(quint16 port) {
    try {
        _handler->setServerPort(port);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

IServerConfigurationProvider::INTERNET_PROTOCOL::ip ServiceClientAdapter::getInternetProtocol() const {
    try {
        ServerConfigHandler::INTERNET_PROTOCOL ip = _handler->getInternetProtocol();
        if (ip == ServerConfigHandler::IPv4)
            return IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4;
        if (ip == ServerConfigHandler::IPv6)
            return IServerConfigurationProvider::INTERNET_PROTOCOL::IPv6;
        return IServerConfigurationProvider::INTERNET_PROTOCOL::undefined;
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::setInternetProtocol(IServerConfigurationProvider::INTERNET_PROTOCOL::ip ip) {
    try {
        if (ip == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4)
            _handler->setInternetProtocol(ServerConfigHandler::IPv4);
        else if (ip == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv6)
            _handler->setInternetProtocol(ServerConfigHandler::IPv6);
        else
            _handler->setInternetProtocol(ServerConfigHandler::undefined);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

quint16 ServiceClientAdapter::getIdleTimeout() const {
    try {
        return _handler->getIdleTimeout();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::setIdleTimeout(quint16 timeout) {
    try {
        _handler->setIdleTimeout(timeout);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

quint16 ServiceClientAdapter::getDataConnectionTimeout() const {
    try {
        return _handler->getDataConnectionTimeout();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::setDataConnectionTimeout(quint16 timeout) {
    try {
        _handler->setDataConnectionTimeout(timeout);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

bool ServiceClientAdapter::isUsingSystemUser() const {
    try {
        return _handler->isUsingSystemUser();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::useSystemUser(bool use) {
    try {
        _handler->useSystemUser(use);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

bool ServiceClientAdapter::isAnonymousAllowed() const {
    try {
        return _handler->isAnonymousAllowed();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::allowAnonymous(bool allow) {
    try {
        return _handler->allowAnonymous(allow);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

bool ServiceClientAdapter::isAnonymousUploadAllowed() const {
    try {
        return _handler->isAnonymousUploadAllowed();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::allowAnonymousUpload(bool allow) {
    try {
        _handler->allowAnonymousUpload(allow);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

bool ServiceClientAdapter::isAnonymousCreateDirAllowed() const {
    try {
        return _handler->isAnonymousCreateDirAllowed();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::allowAnonymousCreateDir(bool allow) {
    try {
        _handler->allowAnonymousCreateDir(allow);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth ServiceClientAdapter::getVirtualUserAuthentication() const {
    try {
        return IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::Anonymous;
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::setVirtualUserAuthentication(IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth mode) {
    try {
        _handler->setVirtualUserAuthentication(ServerConfigHandler::Anonymous);
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::addVirtualUser(const QString& user, const QString& password) {
    try {
        _handler->addVirtualUser(user.toStdString().c_str(), password.toStdString().c_str());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::remVirtualUser(const QString& user) {
    try {
        _handler->remVirtualUser(user.toStdString().c_str());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

QStringList ServiceClientAdapter::virtualUsers() const {
    try {
        QStringList list;
        ServerConfigHandler::StringSequence* input = _handler->virtualUsers();
        for (unsigned int i = 0; i < input->length(); i++) {
            list << QString((*input)[i]);
        }
        return list;
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

QString ServiceClientAdapter::getWelcomeMessage() const {
    try {
        return QString(_handler->getWelcomeMessage());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::setWelcomeMessage(const QString& message) {
    try {
        _handler->setWelcomeMessage(message.toStdString().c_str());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

QString ServiceClientAdapter::getLogFile() const {
    try {
        return QString(_handler->getLogFile());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::importConfiguration(const QString& configuration) {
    try {
        _handler->importConfiguration(configuration.toStdString().c_str());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

QString ServiceClientAdapter::exportConfiguration() const {
    try {
        return QString(_handler->exportConfiguration());
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::resetConfiguration() {
    try {
        _handler->resetConfiguration();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::start() const {
    try {
        _handler->start();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::stop() const {
    try {
        _handler->stop();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}

void ServiceClientAdapter::restart() const {
    try {
        _handler->restart();
    } catch (...) {
        throw CommunicationException(ACCESS_ERROR_MESSAGE);
    }
}


} // Impl
} // CORBA
