#ifndef CHROOTLIST_H
#define CHROOTLIST_H

#include <QFile>

#include "abstractauthentication.h"

class ChrootList : public AbstractAuthentication
{
public:
    ChrootList(const QString & chrootFile);

protected:
    bool update();
    bool refresh();

private :
    QFile m_passFile;
};

#endif // CHROOTLIST_H
