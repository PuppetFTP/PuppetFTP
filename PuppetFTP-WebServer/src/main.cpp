/*
 * PuppetFTPWebServer.h
 *
 *  Created on: 1 oct. 2012
 *      Author: laplace
 */

#include <qglobal.h>
#include <QtCore/QCoreApplication>
#include "log/log.h"
#include "PuppetFTPWebServer.h"

int main(int argc, char *argv[]) {
    qInstallMsgHandler(logMessage);
    QCoreApplication a(argc, argv);
    HTTPServer server;
    server.configure();
    server.start();
    return a.exec();
//    PuppetFTPWebServer service(argc, argv);
//    return service.exec();
}
