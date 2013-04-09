/*
 * CommunicationService.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include <QString>
#include <QMap>
#include <QDebug>
#include "CommunicationService.h"
#include "CommunicationException.h"


QMutex                CommunicationService::_lock;
CommunicationService* CommunicationService::_instance = 0;

/********************************************************************************
 * Private constructors, destructor and assign operator
 */
CommunicationService::CommunicationService() : _provider(0) {
}

CommunicationService::~CommunicationService() {
	if (_provider != 0) {
		_provider->unconfigure();
		delete _provider;
	}
}

void CommunicationService::instance() {
    _lock.lock();
    if (_instance == 0) {
        _instance = new CommunicationService();
    }
    _lock.unlock();
}

/********************************************************************************
 * Functions
 */
INetworkAccessProvider* CommunicationService::provider() {
    instance();
    if (_instance->_provider == 0) {
        throw CommunicationException("No provider defined.");
    }
    return _instance->_provider;
}

void CommunicationService::setProvider(INetworkAccessProvider* provider) {
    instance();
    _instance->_provider = provider;
}

void CommunicationService::configure(INetworkAccessProvider::MODE::mode mode, const QMap<QString, QString>& options) {
    instance();
    if (_instance->_provider == 0) {
        throw CommunicationException("No provider defined.");
    }
    // Register custom type into QMetaType system
    qRegisterMetaType<IServerConfigurationProvider::INTERNET_PROTOCOL::ip>("IServerConfigurationProvider_INTERNET_PROTOCOL");
    qRegisterMetaType<IServerConfigurationProvider::VIRTUAL_USER_AUTHENTICATION::auth>("IServerConfigurationProvider_VIRTUAL_USER_AUTHENTICATION");
    qRegisterMetaTypeStreamOperators<int>("IServerConfigurationProvider_INTERNET_PROTOCOL");
    qRegisterMetaTypeStreamOperators<int>("IServerConfigurationProvider_VIRTUAL_USER_AUTHENTICATION");
    // Configure provider
    try {
        _instance->_provider->configure(mode, options);
    } catch (const CommunicationException& e) {
        qCritical() << "Error while configuring the network provider: " << e.message();
    }
}

void CommunicationService::dispose() {
    if (_instance != 0) {
        delete _instance;
        _instance = 0;
    }
}
