#include "pamauthentication.h"

PamAuthentication::PamAuthentication(const QString & chrootFile)
    : m_passFile(chrootFile)
{
}

bool PamAuthentication::update()
{

    return true;
}

bool PamAuthentication::refresh()
{

    return false;
}
