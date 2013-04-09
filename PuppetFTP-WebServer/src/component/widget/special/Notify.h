#ifndef NOTIFY_H
#define NOTIFY_H

#include "AbstractWidget.h"
#include "IInlinable.h"

namespace UI {

class Notify: public AbstractWidget, public IInlinable {
public:
    enum SEVERITY { INFO, WARNING, ERROR, NONE };

protected:
    QMap< SEVERITY, QList<IInlinable*> >  _notify;

public:
    Notify();
    ~Notify();

    void                                 addNotice(IInlinable *notice, SEVERITY severity = NONE);
    void                                 addNotice(QPair<QString, SEVERITY> notice);
    void                                 addNotice(const QString& text, SEVERITY severity = NONE);
    QList<IInlinable*>                   getNotice(SEVERITY severity) const;
    QMap< SEVERITY, QList<IInlinable*> > getNotice()                  const;
    QString                              render()                     const;
};

} // namespace UI

#endif // NOTIFY_H
