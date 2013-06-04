#ifndef PROFTPDPARSER_H
#define PROFTPDPARSER_H

#include <QString>
#include <QVariant>
#include <QHash>
#include <QElapsedTimer>

#include <lasterror.h>

#define DEFAULT_CONFIG_PROFTPD_FILE "/etc/proftpd/proftpd.conf"
#define DEFAULT_BIN_PATH_PROFTPD "/etc/init.d/proftpd"

#define CACHE_TIME 30000

class ProftpdConfNode : public QHash < QString, QString >
{
public:
    ProftpdConfNode();
    ProftpdConfNode(const ProftpdConfNode & node);
    ProftpdConfNode(const QString & data);
    ~ProftpdConfNode();

    ProftpdConfNode operator=(const ProftpdConfNode & node);

    void addChild(const QString & key, const ProftpdConfNode & child);
    void removeChild(const QString & key);
    QHash < QString, ProftpdConfNode > childreen() const;

private:
    QHash < QString, ProftpdConfNode > m_childreen;
};

class ProftpdParser : public LastError
{
public:
    ProftpdParser(const QString & filePath = DEFAULT_CONFIG_PROFTPD_FILE);

    void set(const QString & key, const QVariant & value = QVariant(), bool toDelete = false);
    QVariant get(const QString & key);

    QString fileName() const;
    void setFileName(const QString & filename);

    bool isDryRun() const;
    void setDryRun(bool dryRun);

private:
    ProftpdConfNode parse(const QString & data);
    void insert(QString & data, const QString & key, const QString & value, bool toDelete);

    void refresh();
    void flush();

private:
    QString m_filename;
    bool m_dryRun;

    QString m_data;
    ProftpdConfNode m_cache;
    QElapsedTimer m_cacheTimer;
};

#endif // PROFTPDPARSER_H
