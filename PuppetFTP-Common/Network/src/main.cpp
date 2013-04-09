/*
 * main.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include "CommunicationService.h"
#include "CommunicationException.h"
#include "INetworkAccessProvider.h"
#include "CORBAImpl/Provider.h"
#include "TestServerConfigProvider.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QMap<QString, QString> options;
    options["InitRef"] = "NameService=corbaloc:iiop:localhost:2809/NameService";

    try {
        // Configure configuration layer...
        CommunicationService::setProvider(new CORBA::Impl::Provider());
        CommunicationService::configure(INetworkAccessProvider::MODE::SERVER, options);

        // Add a server configuration handler...
        IServerConfigurationProvider* server = new TestServerConfigProvider();
        CommunicationService::provider()->registerServiceProvider(TEST_SERVER_NAME, server);

        // Get a client for the previously added handler...
        IServerConfigurationProvider* client = CommunicationService::provider()->getServiceClient(server->getServerName());

        // Call some methods...
        std::cout << "SERVER "
                  << client->getServerName().toStdString()
                  << " ON "
                  << client->getServerAddr().toStdString() << ":" << client->getServerPort()
                  << std::endl
                  << "IS SERVER USING SYSTEM USER: " << (client->isUsingSystemUser()  == true ? "yes" : "no") << std::endl
                  << "IS ANONYMOUS USER ALLOWED: "   << (client->isAnonymousAllowed() == true ? "yes" : "no") << std::endl;

        std::cout << "TRY TO CHANGE THE ANONYMOUS CONFIGURATION:" << std::endl
                  << "   is allowed          : " << (client->isAnonymousAllowed()          == true  ? "yes" : "no") << std::endl
                  << "   can upload          : " << (client->isAnonymousUploadAllowed()    == true  ? "yes" : "no") << std::endl
                  << "   can create directory: " << (client->isAnonymousCreateDirAllowed() == true  ? "yes" : "no") << std::endl;

        client->allowAnonymous(true);
        client->allowAnonymousUpload(true);
        client->allowAnonymousCreateDir(true);

        std::cout << "NEW CONFIGURATION:" << std::endl
                  << "   is allowed          : " << (client->isAnonymousAllowed()          == true  ? "yes" : "no") << std::endl
                  << "   can upload          : " << (client->isAnonymousUploadAllowed()    == true  ? "yes" : "no") << std::endl
                  << "   can create directory: " << (client->isAnonymousCreateDirAllowed() == true  ? "yes" : "no") << std::endl;

        std::cout << "VIRTUAL USERS:" << std::endl;
        QStringList vusers = client->virtualUsers();
        for (QStringList::iterator it = vusers.begin(); it != vusers.end(); it++) {
            std::cout << (*it).toStdString() << std::endl;
        }
        delete client;


        std::cout << std::endl << std::endl << "Sleep 10s..." << std::endl;
        ::sleep(10);
        // Get a client for the previously added handler...
        client = CommunicationService::provider()->getServiceClient(server->getServerName());
        // Call some methods...
        std::cout << "SERVER " << client->getServerName().toStdString();

    } catch (const CommunicationException& e) {
        qCritical() << e.message();
    }
    return a.exec();
}

