#include "lasterror.h"

/*!
    \class LastError
    \brief LastError class provide easy support to hold internal error messages
 */
LastError::LastError()
{
}

QString LastError::lastError()
{
    const QString & lastError = m_lastError;
    m_lastError.clear();
    return lastError;
}

bool LastError::hasFailure()
{
    return m_lastError.isEmpty();
}

void LastError::setLastError(const QString & lastError)
{
    m_lastError = lastError;
}
