#include "Breadcrumb.h"
#include "Text.h"
#include "Link.h"

namespace UI {

Breadcrumb::Breadcrumb() {
}

Breadcrumb::~Breadcrumb() {
}

QList<IInlinable*> Breadcrumb::getLink()                                     const { return _lists;   }
void               Breadcrumb::addLink(IInlinable* link)                           { _lists << link;  }
void               Breadcrumb::addLinks(QList<IInlinable*> lists)                  { _lists << lists; }
void               Breadcrumb::addLink(const QString& text, const QString& url)    {
    if (!url.isEmpty()) {
        Link* link = new Link(url, new Text(text));
        _lists << link;
    } else {
        _lists << new Text(text);
    }
}

void            Breadcrumb::addLinks(QMap<QString, QString> lists) {
    for (QMap<QString, QString>::const_iterator it = lists.begin(); it != lists.end(); it++) {
        addLink(it.key(), it.value());
    }
}

void            Breadcrumb::setLinks(QList<IInlinable*> lists) {
    _lists = lists;
}

QString         Breadcrumb::render() const {
    QString res;

    for (QList<IInlinable*>::const_iterator it = _lists.begin(); it != _lists.end(); it++) {
        if (!res.isEmpty())
            res.append(" :: ");
        res.append((*it)->render());
    }
    return res;
}

} // namespace UI
