#include "puppetftpservice.h"
#include "serverconfig.h"
#include "CommunicationService.h"
#include "CORBAImpl/Provider.h"
#include "CommunicationException.h"

PuppetFtpService::PuppetFtpService(int argc, char ** argv)
    : QtService < QCoreApplication > (argc, argv, SERVICE_NAME)
{
    setServiceDescription("Easy FTP daemon manager");
    setServiceFlags(QtServiceBase::Default);
}

PuppetFtpService::~PuppetFtpService()
{
}

void PuppetFtpService::start()
{
    QCoreApplication * app = application();
    ServerConfig     * config = ServerConfig::getInstance();

    config->load();
    logMessage(QString("Valid conf file : %1").arg(config->isValid()), Information);
    logMessage(QString("Conf file : %1").arg(config->getSettings().fileName()), Information);
    logMessage(QString("Use bin : %1").arg(config->get(ServerConfig::binPathName)), Information);

    // Inititiate configuration handler
    QMap<QString, QString> options;
    options["InitRef"] = QString("NameService=corbaloc:iiop:%1:%2/NameService").arg(config->get(ServerConfig::omninameAddrName),
                                                                                    config->get(ServerConfig::omninamePortName));

    logMessage(QString(QLatin1String("InitRef is: %1")).arg(options["InitRef"]), Information);
    logMessage(QString(QLatin1String("Use configuration file: %1")).arg(config->get(ServerConfig::configFileName)), Information);
    // Configure configuration layer...
    try {
        CommunicationService::setProvider(new CORBA::Impl::Provider());
        CommunicationService::configure(INetworkAccessProvider::MODE::SERVER, options);

        QString serverName = config->get(ServerConfig::serverNameName);
        if (serverName.isEmpty()) {
            logMessage(QLatin1String("Unable to find serverName in puppetFTP configurationFile: %1"), Error);
            stop();
            return;
        }

        CommunicationService::provider()->registerServiceProvider(serverName, (IServerConfigurationProvider *)&m_metaConfigDriver);
    } catch (CommunicationException e) {
        logMessage(QString(QLatin1String("Unable to register object: %1")).arg(e.message()), Error);
        stop();
        return;
    }

    app->exec();
}

void PuppetFtpService::stop()
{
    // Properly stop m_orb
    // m_orb->shutdown(false); ?

    logMessage(QLatin1String("Shutting Down puppetftp service"));
    application()->quit();
    ServerConfig::destroyInstance();
}

#ifndef QT_NO_DEBUG
#include <QDebug>
void PuppetFtpService::logMessage(const QString & message, MessageType type, int id, uint category, const QByteArray & data)
{
    QString logType;
    switch (type) {
    case Success: logType = QLatin1String("SUCC:"); break;
    case Error: logType = QLatin1String("ERRO:"); break;
    case Warning: logType = QLatin1String("WARN:"); break;
    case Information: logType = QLatin1String("INFO:"); break;
    default: break;
    }

    qDebug() << logType + message;
    QtService<QCoreApplication>::logMessage(message, type, id, category, data);
}
#endif // QT_NO_DEBUG
