#ifndef BREADCRUMB_H
#define BREADCRUMB_H

#include "AbstractWidget.h"
#include "IInlinable.h"

namespace UI {

class Breadcrumb: public AbstractWidget, public IInlinable {
protected:
    QList<IInlinable*>    _lists;
public:
    Breadcrumb();
    ~Breadcrumb();

    QList<IInlinable*>    getLink() const;

    void    addLink(IInlinable* link);
    void    addLink(const QString& text, const QString& url);
    void    addLinks(QList<IInlinable*> lists);
    void    addLinks(QMap<QString, QString> lists);
    void    setLinks(QList<IInlinable*> lists);

    QString render() const;
};

} // namespace UI

#endif // BREADCRUMB_H
