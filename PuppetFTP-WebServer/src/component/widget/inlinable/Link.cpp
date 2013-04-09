#include "Link.h"

namespace UI {

Link::Link() {
    _url    = "";
    _widget = NULL;
}

Link::Link(const QString& url) {
    _url    = url;
    _widget = NULL;
}

Link::Link(const QString& url, IInlinable* widget) {
    _url    = url;
    _widget = widget;
}

Link::Link(const Link& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
}

Link& Link::operator=(const Link& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
    return *this;
}

Link::~Link() {
    delete _widget;
}


void            Link::setWidget(IInlinable* widget) { _widget = widget; }
void            Link::setUrl(const QString& url)    { _url = url;       }
IInlinable*     Link::getWidget()             const { return _widget;   }
QString         Link::getUrl()                const { return _url;      }

QString         Link::render()                const {
    QString res;

    res.append("<a" + renderAttribute() + " href=\"");
    res.append(_url);
    res.append("\">");
    if (_widget != NULL) {
        res.append(_widget->render());
    }
    res.append("</a>");
    return res;
}

} // namespace UI
