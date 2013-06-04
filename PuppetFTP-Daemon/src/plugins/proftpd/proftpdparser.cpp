#include <QDir>
#include <QTextStream>

#include <QDebug>

#include "ServerConfigHandler.hh"
#include "proftpdparser.h"

ProftpdConfNode::ProftpdConfNode()
    : QHash < QString, QString >()
{
}

ProftpdConfNode::ProftpdConfNode(const ProftpdConfNode & node)
    : QHash < QString, QString >(node)
{
    m_childreen = node.childreen();
}

ProftpdConfNode::~ProftpdConfNode()
{
}

ProftpdConfNode ProftpdConfNode::operator=(const ProftpdConfNode & node)
{
    if (this != &node) {
        QHash < QString, QString >::operator=(node);
        m_childreen = node.childreen();
    }

    return *this;
}

void print(const ProftpdConfNode & node)
{
    QHashIterator < QString, QString > i(node);

    qDebug() << "PRINT";

    /*
    while(i.hasNext()) {
        i.next();
        qDebug() << "> " << i.key() << "->" << i.value();
    }
    */
    QHashIterator < QString , ProftpdConfNode > j(node.childreen());

    while (j.hasNext()) {
        j.next();
        qDebug() << j.key() << " begin";
        print(j.value());
        qDebug() << j.key() << " end";
    }

    qDebug() << "ENDPRINT";
}

void ProftpdConfNode::addChild(const QString & key, const ProftpdConfNode & child)
{
    m_childreen.insert(key, child);
}

void ProftpdConfNode::removeChild(const QString & key)
{
    m_childreen.remove(key);
}

QHash < QString, ProftpdConfNode > ProftpdConfNode::childreen() const
{
    return m_childreen;
}

ProftpdParser::ProftpdParser(const QString & filePath)
    : m_filename(QDir::toNativeSeparators(filePath))
{
}

//#define BEGIN_NODE_REGEXP "\\n\\s*<([^>\\s]+)\\s+([^>]+)>"
#define BEGIN_NODE_REGEXP "(?:\\n\\s*|^\\s*)<([^>\\n\\s]+)[\\t| ]+([^>\\n]+)>(?:\\n|$)|(?:\\n\\s*|^\\s*)<([^>\\s]+)>(?:\\n|$)"
//#define DATA_NODE_REGEXP "\\n\\s*([^#<\\n\\s]+)\\s+([^\\s\\n][^\\n]*)"

#define DATA_NODE_REGEXP "(?:\\n\\s*|^\\s*)([^#<>\\n\\s]+)[\\t| ]+([^>\\s\\n][^>\\n]*)(?:\\n|$)|(?:\\n\\s*|^\\s*)([^#<>\\n\\s]+)[\\t| ]*(?:\\n|$)"

ProftpdConfNode ProftpdParser::parse(const QString & data)
{
    qDebug() << "data";
    qDebug() << data;
    qDebug() << "dataEND";

    ProftpdConfNode node;
    QRegExp beginNode(BEGIN_NODE_REGEXP, Qt::CaseSensitive, QRegExp::RegExp2);
    QRegExp datamatch(DATA_NODE_REGEXP, Qt::CaseSensitive, QRegExp::RegExp2);

    int childpos = 0;
    int datapos = 0;
    while ((childpos = beginNode.indexIn(data, childpos)) != -1) {

        while ((datapos = datamatch.indexIn(data, datapos)) != -1 && datapos < childpos) {
            datapos += datamatch.matchedLength() - 1;

        //    qDebug() << "DATAA" << data.right(datapos);
            if (datamatch.cap(1) == QLatin1String("Include"))
                continue;

            datamatch.cap(1).isEmpty() ?
                node.insert(datamatch.cap(3), QString())
                : node.insert(datamatch.cap(1), datamatch.cap(2));
        }

        childpos += beginNode.matchedLength() - 1;
        int beginData = childpos;
        QRegExp endNode(QString("(</%1>)").arg(beginNode.cap(1).isEmpty() ? beginNode.cap(3) : beginNode.cap(1)));
        childpos = endNode.indexIn(data, childpos);

        if (childpos == -1)
            setLastError(QLatin1String("Misformated configuration file"));

  //      qDebug() << "ADD" << beginNode.capturedTexts();
        int endData = childpos;
        childpos += endNode.matchedLength();
        datapos = childpos;
        node.addChild(beginNode.cap(1).isEmpty() ? beginNode.cap(3) : beginNode.cap(1) + " " + beginNode.cap(2),
                      parse(data.mid(beginData).left(endData - beginData)));
    }
 //   qDebug() << "DATAB" << data.right(datapos)<< "DATABEND";
    while ((datapos = datamatch.indexIn(data, datapos)) != -1) {
        datapos += datamatch.matchedLength() - 1;
        if (datamatch.cap(1) == QLatin1String("Include"))
            continue;

 //       qDebug() << "DATA" << data.right(datapos) << "DATA END";
//qDebug() << datamatch.matchedLength() << datamatch.captureCount() << datamatch.capturedTexts();
        datamatch.cap(1).isEmpty() ?
            node.insert(datamatch.cap(3), QString())
            : node.insert(datamatch.cap(1), datamatch.cap(2));
    }

    return node;
}

void ProftpdParser::insert(QString & data, const QString & key, const QString & value, bool toDelete)
{
    QStringList subkeys = key.split(QLatin1Char('#'));
    const QString & currentKey = subkeys.first();
    bool iscurrentKeyNode = (subkeys.count() > 1);

    QRegExp beginNode(BEGIN_NODE_REGEXP);
    QRegExp datamatch(DATA_NODE_REGEXP);

    int childpos = 0;
    int datapos = 0;
    while ((childpos = beginNode.indexIn(data, childpos)) != -1) {
        if (!iscurrentKeyNode) {
            while ((datapos = datamatch.indexIn(data, datapos)) != -1 && datapos < childpos) {
                if (datamatch.cap(1) == currentKey) {
                    if (toDelete) {
                        data.replace(datapos, datamatch.matchedLength(), QString());
                        return;
                    }

                    QString other = data.mid(datapos).left(datamatch.matchedLength()).replace(QRegExp(datamatch.cap(2)), value);
                    data.replace(datapos, datamatch.matchedLength(), other);
                    return;
                }

                if (datamatch.cap(3) == currentKey) {
                    if (toDelete) {
                        data.replace(datapos, datamatch.matchedLength(), QString());
                        return;
                    }

                    const QString other = data.mid(datapos).left(datamatch.matchedLength()) + QString("\t") + value;
                    data.replace(datapos, datamatch.matchedLength(), other);
                    return;
                }

                datapos += datamatch.matchedLength() - 1;
            }
        }

        childpos += beginNode.matchedLength() - 1;
        int beginData = childpos;
        QRegExp endNode(QString("(</%1>)").arg(beginNode.cap(1).isEmpty() ? beginNode.cap(3) : beginNode.cap(1)));
        childpos = endNode.indexIn(data, childpos);

        if (childpos == -1)
            setLastError(QLatin1String("Misformated configuration file"));

        int endData = childpos;
        childpos += endNode.matchedLength();
        datapos = childpos;

        if ((currentKey.split(QString(" ")).first() == beginNode.cap(1) ||
             currentKey.split(QString(" ")).first() == beginNode.cap(3)) &&
            !subkeys.isEmpty()) {
            subkeys.removeFirst();
            QString inner = data.mid(beginData).left(endData - beginData);
            insert(inner, subkeys.join(QString("#")), value, toDelete);
            data.replace(beginData, endData - beginData, inner);
            return;
        }
    }

    if (iscurrentKeyNode) {
        data.prepend(QString("<%1>\n</%2>\n").arg(currentKey, currentKey.split(QString(" ")).first()));
        insert(data, subkeys.join(QString("#")), value, toDelete);
    } else {
        while ((datapos = datamatch.indexIn(data, datapos)) != -1) {
            if (datamatch.cap(1) == currentKey) {
                if (toDelete) {
                    data.replace(datapos, datamatch.matchedLength(), QString());
                    return;
                }

                const QString other = data.mid(datapos).left(datamatch.matchedLength()).replace(QRegExp(datamatch.cap(2)), value);
                data.replace(datapos, datamatch.matchedLength(), other);
                return;
            }

            if (datamatch.cap(3) == currentKey) {
                if (toDelete) {
                    data.replace(datapos, datamatch.matchedLength(), QString());
                    return;
                }

                const QString other = data.mid(datapos).left(datamatch.matchedLength()) + QString(" ") + value;
                data.replace(datapos, datamatch.matchedLength(), other);
                return;
            }

            datapos += datamatch.matchedLength() - 1;
        }

        if (toDelete)
            return;

        if (value.isEmpty())
            data.prepend(QString("\n%1").arg(key));
        else
            data.prepend(QString("\n%1\t%2").arg(key, value));
    }
}

void ProftpdParser::refresh()
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

    if (!m_data.isEmpty()) {
        m_cache.clear();
        m_cache = parse(m_data);
    }

    m_cacheTimer.start();
}

void ProftpdParser::flush()
{
    QFile file(m_filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        if (file.write(m_data.toUtf8()) == -1)
            file.close();
        else
            setLastError(QLatin1String("An error occured while writting data to the file."));
    } else {
        setLastError(QLatin1String("Unable to access configuration file."));
    }
}

void ProftpdParser::set(const QString & key, const QVariant & value, bool toDelete)
{
    if (!isDryRun())
        refresh();

    insert(m_data, key, value.toString(), toDelete);

    if (!isDryRun())
        flush();
}

QVariant ProftpdParser::get(const QString & key)
{
    if (!isDryRun())
        refresh();

    ProftpdConfNode node = m_cache;
    QStringList keyList = key.split(QLatin1Char('#'));
    foreach (const QString subkey, keyList) {
        if (subkey != keyList.last()) {
            node = node.childreen().value(subkey, ProftpdConfNode());
            qDebug() << node;
        } else {
            if (node.contains(subkey))
                return QVariant(node.value(subkey, QString()));
        }
    }

    return QVariant(QVariant::Invalid);
}

QString ProftpdParser::fileName() const
{
    return m_filename;
}

void ProftpdParser::setFileName(const QString & filename)
{
    m_filename = filename;
}

bool ProftpdParser::isDryRun() const
{
    return m_dryRun;
}

void ProftpdParser::setDryRun(bool dryRun)
{
    m_dryRun = dryRun;
}
