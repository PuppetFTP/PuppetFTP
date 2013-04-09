#ifndef ABSTRACTPLUGINEXCEPTION_H
#define ABSTRACTPLUGINEXCEPTION_H

#include <QString>

class AbstractPluginException
{
public:
    enum    Error
    {
        NoError,
        NoPluginAvailable,
        InvalidCast
    };

    AbstractPluginException(Error err);
    AbstractPluginException(Error err, QString ext);
    ~AbstractPluginException();

    QString                         toQString();

private:
    Error   _err;
    QString _ext;
};

#endif // ABSTRACTPLUGINEXCEPTION_H
