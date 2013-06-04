#include <QDir>
#include <QProcess>
#include <QTextStream>
#include "vsftpdparser.h"

VsftpdParser::VsftpdParser(const QString & filePath)
{
    setFileName(QDir::toNativeSeparators(filePath));
}

void VsftpdParser::refresh()
{
    if (!m_cacheTimer.hasExpired(CACHE_TIME))
        return;

    if (m_data.isEmpty()) {
        QFile file(m_filename);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            m_data = in.readAll();
        } else {
            setLastError(QLatin1String("Unable to access configuration file."));
        }
    }

    m_cache.clear();
    QStringList options = m_data.split(QChar::LineSeparator, QString::SkipEmptyParts);
    foreach(const QString & option, options) {
        const QStringList & element = option.split(QLatin1Char('='));
        if (element.size() >= 2)
            m_cache.insert(element.at(0), QVariant(element.at(1)));
    }

    m_cacheTimer.start();
}

void VsftpdParser::flush()
{
    QFile file(m_filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        if (file.write(m_data.toUtf8()) == -1) {
            file.close();
        } else {
            setLastError(QLatin1String("An error occured while writting data to the file."));
        }
    } else {
        setLastError(QLatin1String("Unable to access configuration file."));
    }
}

void VsftpdParser::set(const QString & key, const QVariant & value)
{
    if (!isDryRun())
        refresh();

    if (value.isValid()) {
        if (m_cache.contains(key)) {
            m_data.replace(QRegExp(QString("(^#?%1=[^\n]+\n)|(#?%1=[^\n]+\n)").arg(key)), QString("%1=%2\n").arg(key, value.toString()));
        } else {
            if (!m_data.endsWith(QChar::LineSeparator))
                m_data.append(QChar::LineSeparator);

            m_data.append(QString(QLatin1String("%1=%2\n")).arg(key, value.toString()));
        }

        m_cache.insert(key, value);
    } else {
        if (!m_cache.contains(key))
            return;

        m_data.remove(QRegExp(QString("(^#?%1=[^\n]+\n)|(#?%1=[^\n]+\n)").arg(key)));
        m_cache.remove(key);
    }

    if (!isDryRun())
        flush();
}

QVariant VsftpdParser::get(const QString & key)
{
    if (!isDryRun())
        refresh();

    return m_cache.value(key, QVariant());
}

QString VsftpdParser::fileName() const
{
    return m_filename;
}

void VsftpdParser::setFileName(const QString filename)
{
    m_filename = filename;
    sync();
}
