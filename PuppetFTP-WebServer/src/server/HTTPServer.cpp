/*
 * HTTPServer.cpp
 *
 *  Created on: 1 oct. 2012
 *      Author: laplace
 */

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
#include <QSettings>
#include <QStringList>
#include "HTTPServer.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "Router.h"
#include "SessionManager.h"
#include "RequestDispatcher.h"
#include "DatabaseManager.h"
#include "Table.h"
#include "UserTable.h"
#include "User.h"
#include "ServerTable.h"
#include "Server.h"
#include "AccessibleServerTable.h"
#include "AccessibleServer.h"
#include "PuppetFTPCredentialTable.h"
#include "ServerCredentialTable.h"
#include "Credential.h"
#include "PuppetFTPRoleTable.h"
#include "ServerRoleTable.h"
#include "Role.h"
#include "ModelEntityFactory.h"

#include "ModelWidgetFactory.h"
#include "UserModelList.h"
#include "RoleModelList.h"
#include "ServerModelList.h"
#include "CredentialModelList.h"
#include "AccessibleServerModelList.h"
#include "UserModelEditor.h"
#include "RoleModelEditor.h"
#include "ServerModelEditor.h"
#include "CredentialModelEditor.h"
#include "AccessibleServerModelEditor.h"
#include "CommunicationService.h"
#include "INetworkAccessProvider.h"
#include "CommunicationException.h"
#include "CORBAImpl/Provider.h"
#include "ServerConfEditor.h"
#include "ServerConfList.h"

QHostAddress HTTPServer::DEFAULT_HOSTADDR        = QHostAddress::Any;
quint16      HTTPServer::DEFAULT_HOSTPORT        = 5074;

HTTPServer::HTTPServer(QObject* parent) :
    QTcpServer(parent) {
}

HTTPServer::~HTTPServer() {
}

void HTTPServer::configure() {
    QSettings settings("config/config.ini", QSettings::IniFormat, this);
    QMap<QString, QString> options;
    QStringList settingsKeys = settings.allKeys();
    for (QStringList::iterator it = settingsKeys.begin(); it != settingsKeys.end(); it++) {
        options[*it] = settings.value(*it).toString();
    }
    // Load routes and configure RequestDispatcher
    Routing::Router::instance()->loadRoutes();
    RequestDispatcher::instance()->configure();
    // Get listen address
    QString addr = settings.value("HostAddress", "ANY").toString();
    _addr = addr == "ANY" ? DEFAULT_HOSTADDR : QHostAddress(addr);
    // Get listen port
    _port = settings.value("HostPort", DEFAULT_HOSTPORT).toInt();
    _port = _port < 1000 ? DEFAULT_HOSTPORT : _port;
    // Get session timeout
    SessionManager::instance()->setSessionTimeout(settings.value("SessionTimeout", SessionManager::DEFAULT_SESSION_TIMEOUT).toUInt());
    // Configure communication layer
    try {
        CommunicationService::setProvider(new CORBA::Impl::Provider());
        CommunicationService::configure(INetworkAccessProvider::MODE::CLIENT, options);
    } catch (const CommunicationException& e) {
        qCritical() << e.message();
    }
    // Configure Entities

    // Configure Database
    QMap<QString, QString> opts;
    DatabaseManager::instance()->configure(opts);
    // Tables
    DatabaseManager::instance()->registerTable<UserTable>("user");
    DatabaseManager::instance()->registerTable<ServerTable>("server");
    DatabaseManager::instance()->registerTable<PuppetFTPCredentialTable>("puppetftp_credential");
    DatabaseManager::instance()->registerTable<PuppetFTPRoleTable>("puppetftp_role");
    DatabaseManager::instance()->registerTable<ServerCredentialTable>("server_credential");
    DatabaseManager::instance()->registerTable<ServerRoleTable>("server_role");
    DatabaseManager::instance()->registerTable<AccessibleServerTable>("accessible_server");
    // Entities
    Model::ModelEntityFactory::instance()->registerEntity<Model::User>("user");
    Model::ModelEntityFactory::instance()->registerEntity<Model::Server>("server");
    Model::ModelEntityFactory::instance()->registerEntity<Model::Credential>("credential");
    Model::ModelEntityFactory::instance()->registerEntity<Model::Role>("role");
    Model::ModelEntityFactory::instance()->registerEntity<Model::AccessibleServer>("accessible_server");

    // Configure ModelFormFactory
    //   List
    UI::ModelWidgetFactory::instance()->registerWidget<UI::UserModelList>("userList");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::RoleModelList>("roleList");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::ServerModelList>("serverList");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::CredentialModelList>("credentialList");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::AccessibleServerModelList>("accessible_serverList");
    // Edit
    UI::ModelWidgetFactory::instance()->registerWidget<UI::UserModelEditor>("userEditor");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::RoleModelEditor>("roleEditor");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::ServerModelEditor>("serverEditor");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::CredentialModelEditor>("credentialEditor");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::AccessibleServerModelEditor>("accessible_serverEditor");
    // Server
    UI::ModelWidgetFactory::instance()->registerWidget<UI::ServerConfEditor>("serverConfigurationEditor");
    UI::ModelWidgetFactory::instance()->registerWidget<UI::ServerConfList>("serverConfigurationList");
}

void HTTPServer::start() {
    listen(_addr, _port);
    qDebug().nospace() << "Server now listen on " << _addr.toString() << ":" << _port;
}

void HTTPServer::incomingConnection(int socket) {
    QTcpSocket* s = new QTcpSocket(this);
    connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
    s->setSocketDescriptor(socket);
}

void HTTPServer::readClient() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    if (socket->canReadLine()) {
        HTTPRequest request(socket->peerAddress());
        while (socket->bytesAvailable()) {
            request << socket->read(socket->bytesAvailable());
        }
        HTTPResponse response = RequestDispatcher::instance()->dispatch(request);
        QDataStream os(socket);
        os << response.toByteArray();
        socket->close();
        if (socket->state() == QTcpSocket::UnconnectedState) {
            delete socket;
        }
    }
}

void HTTPServer::discardClient() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();
}
