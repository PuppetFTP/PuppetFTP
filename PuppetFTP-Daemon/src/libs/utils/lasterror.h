#ifndef LASTERROR_H
#define LASTERROR_H

#include <QString>

class LastError
{
public:
    LastError();

    QString lastError();
    bool hasFailure();

protected:
    void setLastErrorString(const QString & lastError);

private:
    QString m_lastError;
};

#endif // LASTERROR_H
