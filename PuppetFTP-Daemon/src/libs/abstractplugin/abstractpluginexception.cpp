#include "abstractpluginexception.h"

AbstractPluginException::AbstractPluginException(Error error)
    : _err(error)
{
}

AbstractPluginException::AbstractPluginException(Error error, QString ext)
    : _err(error), _ext(ext)
{
}

AbstractPluginException::~AbstractPluginException()
{
}

QString AbstractPluginException::toQString()
{
    switch (_err)
    {
        case AbstractPluginException::NoPluginAvailable :
            return QString("No plugin available at " + _ext);
        case AbstractPluginException::InvalidCast :
            return QString("An error occured when trying to cast an instance of IConfigHandler to a POA_ServerConfigHandler's reference.");
        default:
            return QString("No error have been detected.");
    }
}

