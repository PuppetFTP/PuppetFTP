#include "plugin.h"

Plugin::Plugin()
{
}

QString Plugin::name()
{
    return m_name;
}

QString Plugin::type()
{
    return m_type;
}

QString Plugin::path()
{
    return m_path;
}

void Plugin::setName(const QString & name)
{
    m_name = name;
}

void Plugin::setType(const QString & type)
{
    m_type = type;
}

void Plugin::setPath(const QString & path)
{
    m_path = path;
}

