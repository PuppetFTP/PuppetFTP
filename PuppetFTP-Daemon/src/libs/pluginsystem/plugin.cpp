#include "plugin.h"

/*!
 * \class Plugin
 * \brief The Plugin class provides the base functionnality common to all plugin types
 *
 *  A new Plugin derived class must exporting the plugin  my using the EXPORT_PLUGIN statement
 */

/*!
 * \property Plugin::name
 * \brief the final plugin name (ex: ProFtpd, VsFtpd)
 */

/*!
 * \property Plugin::type
 * \brief the final plugin type (ex: Metadata)
 */

/*!
 * \property Plugin::group
 * \brief the final plugin group (ex: Ftp)
 */

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

QString Plugin::group()
{
    return m_group;
}

void Plugin::setName(const QString & name)
{
    m_name = name;
}

void Plugin::setType(const QString & type)
{
    m_type = type;
}

void Plugin::setGroup(const QString & group)
{
    m_group = group;
}

