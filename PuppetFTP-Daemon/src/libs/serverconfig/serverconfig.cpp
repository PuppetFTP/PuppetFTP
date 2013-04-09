#include "serverconfig.h"
#include <iostream>

QString ServerConfig::binPathName = "bin_path";
QString ServerConfig::configFileName = "conf_file";
QString ServerConfig::omninameAddrName = "omniname_addr";
QString ServerConfig::omninamePortName = "omniname_port";
QString ServerConfig::pluginPathName = "plugin_path";
QString ServerConfig::serverNameName = "server_name";
QString ServerConfig::serverAddrName = "server_addr";

ServerConfig    *ServerConfig::m_instance = NULL;

ServerConfig::ServerConfig()
    : m_filePath(QDir::toNativeSeparators(QCoreApplication::applicationDirPath().append("/config.ini")))
{
    load();
}

ServerConfig::~ServerConfig()
{
    if (m_settings != NULL)
        delete m_settings;
}

QString     ServerConfig::getFilePath() const
{
    return m_filePath;
}

QSettings   &ServerConfig::getSettings()
{
    return *m_settings;
}

bool        ServerConfig::isValid() const
{
    bool        rightFile;
    bool        err;
    bool        res;
    QFileInfo   infos(m_filePath);

    res = false;
    if (m_settings != NULL)
    {
        rightFile = QFile::exists(m_filePath) && m_settings->fileName().compare(infos.baseName());
        err = !(m_settings->status() == QSettings::NoError);
        res = (!err && rightFile);
    }
    return res;
}

void        ServerConfig::load()
{
    if (m_settings != NULL)
        delete m_settings;
    m_settings = new QSettings(m_filePath, QSettings::IniFormat);
}

QString     ServerConfig::get(QString key)
{
    if (m_settings == NULL)
        return QString();
    return m_settings->value(key).toString();
}

void        ServerConfig::set(QString key, QString value)
{
    if (ServerConfig::m_settings && ServerConfig::m_settings->isWritable())
        ServerConfig::m_settings->setValue(key, QVariant(value));
}

ServerConfig    *ServerConfig::getInstance()
{
    if (ServerConfig::m_instance == NULL)
        ServerConfig::m_instance = new ServerConfig();
    return ServerConfig::m_instance;
}

void            ServerConfig::destroyInstance()
{
    if (ServerConfig::m_instance != NULL)
        delete ServerConfig::m_instance;
}
