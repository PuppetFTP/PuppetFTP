#ifndef VSFTPDPARSER_H
#define VSFTPDPARSER_H

#include <QString>
#include <QVariant>
#include <QSettings>

# define DEFAULT_CONFIG_VSFTP_FILE "/etc/vsftpd/vsftpd.conf"
# define DEFAULT_BIN_PATH_VSFTP "/usr/bin/service"

class VsftpdParser
{
public:
    VsftpdParser(const QString & filePath = DEFAULT_CONFIG_VSFTP_FILE);

    void set(const QString & key, const QVariant & value);
    QVariant get(const QString & key) const;

    QString filename() const;

private:
    QString m_filename;
    QSettings m_confSettings;
};

#endif // VSFTPDPARSER_H
