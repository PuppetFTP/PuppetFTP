/*
 * PuppetFTPWebServer.h
 *
 *  Created on: 27 nov. 2012
 *      Author: laplace
 */

#ifndef PUPPETWEBSERVER_H_
#define PUPPETWEBSERVER_H_

#include <QCoreApplication>
#include "qtservice.h"
#include "HTTPServer.h"

#define SERVICE_NAME "PuppetFTP-WebServer"

class PuppetFTPWebServer: public QtService<QCoreApplication> {
private:
    HTTPServer _server;

    PuppetFTPWebServer();

protected:
    bool configure();
    void start();
    void stop();

public:
    PuppetFTPWebServer(int argc, char* argv[]);
    virtual ~PuppetFTPWebServer();
};

#endif /* PUPPETWEBSERVER_H_ */
