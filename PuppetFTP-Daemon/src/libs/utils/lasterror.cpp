#include "lasterror.h"

LastError::LastError()
{
}

QString LastError::lastError()
{
    return m_lastError;
}

bool LastError::hasFailure()
{
    return m_lastError.isEmpty();
}

void LastError::setLastError(const QString & lastError)
{
    m_lastError = lastError;
}
