
#include "puppetftpservice.h"

// -ORBInitRef NameService=corbaloc:iiop:localhost:2809/NameService

#include <QCoreApplication>
#include <QDebug>

#include "metaconfigdriver.h"

int main(int argc, char ** argv)
{
    /*
    QCoreApplication a(argc, argv);

    QString pluginId = QLatin1String("ProFtpd");
    MetaConfigDriver driver;
    driver.loadPlugin(pluginId, QLatin1String("Proftpd"));

    qDebug() << driver.set(
        pluginId,
        QLatin1String("parserFilename"),
        QVariant(QLatin1String("/home/puppet/Desktop/proftpd.conf"))
    );

    qDebug() << driver.lastErrorString();
    qDebug() << driver.metaProperties(pluginId);
    qDebug() << driver.metaTasks(pluginId);

    qDebug() << driver.exec(pluginId, QLatin1String("stop"));

    qDebug() << driver.get(
        pluginId,
        QLatin1String("anonymousEnable")
    );

    qDebug() << driver.set(
        pluginId,
        QLatin1String("anonymousEnable"),
        false
    );

    qDebug() << driver.get(
        pluginId,
        QLatin1String("anonymousEnable")
    );


    qDebug() << driver.lastErrorString();


    return 7;

    return a.exec();


*/



    PuppetFtpService service(argc, argv);
    return service.exec();
}
