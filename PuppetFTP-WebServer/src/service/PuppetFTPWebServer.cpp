/*
 * PuppetFTPWebServer.cpp
 *
 *  Created on: 27 nov. 2012
 *      Author: laplace
 */

#include <QDebug>
#include <QDir>
#include "PuppetFTPWebServer.h"

PuppetFTPWebServer::PuppetFTPWebServer(int argc, char* argv[]) : QtService<QCoreApplication>(argc, argv, SERVICE_NAME) {
    setServiceDescription("Web server for PuppetFTP");
    setServiceFlags(QtServiceBase::Default);
}

PuppetFTPWebServer::~PuppetFTPWebServer() {
}

bool PuppetFTPWebServer::configure() {
    return true;
}

void PuppetFTPWebServer::start() {
    qDebug() << "WORKING DIRECTORY" << QDir::currentPath();
    _server.configure();
    _server.start();
}

void PuppetFTPWebServer::stop() {
    application()->quit();
}
