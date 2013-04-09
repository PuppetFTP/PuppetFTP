#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QProcess>
#include <QString>
#include <QStringList>

#define INITD "/etc/init.d/%1"

class ServiceManager
{
public:
    static int start(const QString &serviceName);
    static int stop(const QString &serviceName);
    static int restart(const QString &serviceName);

private:
    static int execute(const QString &program, const QStringList &arguments);
};

#endif // SERVICEMANAGER_H
