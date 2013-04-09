#include <QTextStream>
#include <QRegExp>
#include <QStringList>

#include "chrootlist.h"

ChrootList::ChrootList(const QString & chrootFile)
    : AbstractAuthentication()
{
    m_passFile.setFileName(chrootFile);
}

bool ChrootList::update()
{
    if (!m_passFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        return false;

    QTextStream stream(&m_passFile);

    QHashIterator < QString, QString > it(m_users);
    while (it.hasNext()) {
        it.next();
        const QString & data = QString(QLatin1String("%1\n")).arg(it.key());
        stream << data;
    }

    m_passFile.close();
    return true;
}

bool ChrootList::refresh()
{
    if (!m_passFile.open(QIODevice::ReadWrite))
        return false;

    QTextStream stream(&m_passFile);
    QString data = stream.readAll();
    m_passFile.close();

    const QStringList & list = data.split(QRegExp("\n?#"));
    for (int i = 0; i < list.size(); i++) {
        if (!list.at(i).isEmpty())
            m_users.insert(list.at(i), QString());
    }

    return true;
}
