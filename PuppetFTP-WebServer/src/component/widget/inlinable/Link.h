#ifndef LINK_H
#define LINK_H

#include "AbstractWidget.h"
#include "IInlinable.h"

namespace UI {

class Link : public AbstractWidget, public IInlinable {
protected:
    IInlinable*     _widget;
    QString         _url;

private:
    Link();
public:
    Link(const QString& url);
    Link(const QString& url, IInlinable* widget);
    Link(const Link& obj);
    Link& operator=(const Link& obj);
    virtual ~Link();

    void            setWidget(IInlinable* widget);
    void            setUrl(const QString& url);
    IInlinable*     getWidget() const;
    QString         getUrl()    const;
    QString         render()    const;
};

} // namespace UI

#endif // LINK_H
