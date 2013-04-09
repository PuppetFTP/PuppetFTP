#ifndef PUPPETFTPSERVICE_H
#define PUPPETFTPSERVICE_H

#include <qtservice.h>

#include <QtCore>
#include <QtCore/QCoreApplication>
#include <iostream>
//#include "ORB.h"

#include "IServerConfigurationProvider.h"

#define SERVICE_NAME "puppetFtpd"
#define CONFIGFILE_PARAMETER "--config-file="
#define SERVERBINPATH_PARAMETER "--server-bin-path="

class PuppetFtpService : public QtService < QCoreApplication >
{
public:
    PuppetFtpService(int argc, char ** argv);
    ~PuppetFtpService();

protected:
    void start();
    void stop();

#ifndef QT_NO_DEBUG
    void logMessage(const QString & message, MessageType type = Success, int id = 0, uint category = 0, const QByteArray & data = QByteArray());
#endif // QT_NO_DEBUG

private:
    IServerConfigurationProvider * m_server;
};

#endif // PUPPETFTPSERVICE_H
