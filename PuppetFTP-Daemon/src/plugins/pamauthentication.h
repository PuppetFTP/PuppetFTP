#ifndef PAMAUTHENTICATION_H
#define PAMAUTHENTICATION_H

#include <QFile>
#include "abstractauthentication.h"

// apt-get install libpam-pwdfile

class PamAuthentication : public AbstractAuthentication
{
public:
    PamAuthentication(const QString & chrootFile);

protected:
    bool update();
    bool refresh();

private :
    QString m_passFile;
};

#endif // PAMAUTHENTICATION_H
