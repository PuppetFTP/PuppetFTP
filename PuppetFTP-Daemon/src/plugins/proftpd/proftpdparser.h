#ifndef PROFTPDPARSER_H
#define PROFTPDPARSER_H

#include <QString>
#include <QVariant>
#include <QDataStream>

# define DEFAULT_CONFIG_PROFTPD_FILE "/etc/proftpd/proftpd.conf"
# define DEFAULT_BIN_PATH_PROFTPD "/etc/init.d/proftpd"

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

class ProftpdParser
{
public:
    ProftpdParser(const QString & filePath = DEFAULT_CONFIG_PROFTPD_FILE);

    void set(const QString & key, const QVariant & value = QVariant(), bool toDelete = false);
    QVariant get(const QString & key) const;

    QString filename() const;

private:
    ProftpdConfNode parse(const QString & data) const;

private:
    QString m_filename;
    ProftpdConfNode m_data;
};

#endif // PROFTPDPARSER_H
