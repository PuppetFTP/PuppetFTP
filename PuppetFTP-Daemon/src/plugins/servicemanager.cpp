#include "servicemanager.h"

int ServiceManager::start(const QString &serviceName)
{
    return ServiceManager::execute(QString(INITD).arg(serviceName), QStringList() << "start");
}

int ServiceManager::stop(const QString &serviceName)
{
    return ServiceManager::execute(QString(INITD).arg(serviceName), QStringList() << "stop");
}

int ServiceManager::restart(const QString &serviceName)
{
    return ServiceManager::execute(QString(INITD).arg(serviceName), QStringList() << "restart");
}

int ServiceManager::execute(const QString &program, const QStringList &arguments)
{
    QProcess process;
    process.start(program, arguments);
    if (!process.waitForStarted())
        return QProcess::CrashExit;
    if (!process.waitForFinished())
        return QProcess::CrashExit;
    return process.exitStatus();
}
