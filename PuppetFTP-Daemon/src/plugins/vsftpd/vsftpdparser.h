#ifndef VSFTPDPARSER_H
#define VSFTPDPARSER_H

#include <QString>
#include <QVariant>
#include <QHash>
#include <QElapsedTimer>

#include "lasterror.h"

# define DEFAULT_CONFIG_VSFTP_FILE "/etc/vsftpd/vsftpd.conf"
# define DEFAULT_BIN_PATH_VSFTP "/usr/bin/service"

#define CACHE_TIME 30000

class VsftpdParser : public LastError
{
public:
    VsftpdParser(const QString & filePath = DEFAULT_CONFIG_VSFTP_FILE);

    void set(const QString & key, const QVariant & value);
    QVariant get(const QString & key);

    QString fileName() const;
    void setFileName(const QString & filename);

    bool isDryRun() const;
    void setDryRun(bool dryRun);

private:
    void refresh();
    void flush();

private:
    QString m_filename;
    bool m_dryRun;

    QString m_data;
    QHash < QString, QVariant > m_cache;
    QElapsedTimer m_cacheTimer;
};

#endif // VSFTPDPARSER_H
