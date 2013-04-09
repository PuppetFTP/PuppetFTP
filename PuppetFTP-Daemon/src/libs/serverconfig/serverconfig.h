#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QtCore>
#include <QDir>
#include <QFile>
#include <QSettings>

class ServerConfig
{
public:

    static QString      configFileName;
    static QString      binPathName;
    static QString      serverNameName;
    static QString      serverAddrName;
    static QString      pluginPathName;
    static QString      omninameAddrName;
    static QString      omninamePortName;

    ~ServerConfig();

    QString             getFilePath() const;
    QSettings           &getSettings();
    bool                isValid() const;
    void                load();
    QString             get(QString key);
    void                set(QString key, QString value);

    static ServerConfig *getInstance();
    static void         destroyInstance();

private:
    ServerConfig();

    QString             m_filePath;
    QSettings           *m_settings;

    static ServerConfig *m_instance;
};

#endif // SERVERCONFIG_H
