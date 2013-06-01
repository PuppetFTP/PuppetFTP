#include <QDir>
#include <QProcess>
#include <QTextStream>
#include "vsftpdparser.h"
#include "ServerConfigHandler.hh"
#include <iostream>

VsftpdParser::VsftpdParser(const QString & filePath)
    : m_filename(QDir::toNativeSeparators(filePath)), m_confSettings(m_filename, QSettings::NativeFormat)
{
}

void VsftpdParser::set(const QString & key, const QVariant & value)
{
    QFile file(m_filename);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        std::string err("Unable to access configuration file.");
        std::cerr << err << std::endl;
        throw ServerConfigHandler::ConfigurationException(err.c_str());
    }

    QTextStream in(&file);
    QString data = in.readAll();
    bool b_replace = false;

    if (data.contains(QRegExp(QString("(^#?%1=[^\n]+\n)|(#?%1=[^\n]+\n)").arg(key))))
        b_replace = true;

    if (b_replace) {
        data.replace(QRegExp(QString("(^#?%1=[^\n]+\n)|(#?%1=[^\n]+\n)").arg(key)), QString("%1=%2\n").arg(key, value.toString()));
        file.close();

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
            std::string err("Unable to access configuration file.");
            std::cerr << err << std::endl;
            throw ServerConfigHandler::ConfigurationException(err.c_str());
        }

        if (file.write(data.toAscii()) == -1) {
            std::string err("An error occured while writting data to the file.");
            std::cerr << err << std::endl;
            throw ServerConfigHandler::ConfigurationException(err.c_str());
        }
    } else {
        in << QString(QLatin1String("%1=%2\n")).arg(key, value.toString());
    }

    file.close();
    m_confSettings.sync();
}

QVariant VsftpdParser::get(const QString & key) const
{
    if (m_confSettings.status() == QSettings::AccessError) {
        std::string err("Unable to access configuration file.");
        std::cerr << err << std::endl;
        throw ServerConfigHandler::ConfigurationException(err.c_str());
    }

    return m_confSettings.value(key);
}

QString VsftpdParser::filename() const
{
return m_filename;
}
