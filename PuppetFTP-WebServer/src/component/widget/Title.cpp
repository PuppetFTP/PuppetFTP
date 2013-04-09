#include "Title.h"
#include "Text.h"

namespace UI {

Title::Title(const Title::SIZE& size) :
    _size(size) {
}

Title::Title(const QString& title, const Title::SIZE& size) :
    _size(size) {
    if (!title.isEmpty())
        addWidget(new Text(title));
}

Title::Title(IInlinable* widget, const Title::SIZE& size) :
    _size(size) {
    addWidget(widget);
}

Title::Title(const Title& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
    _size       = obj.getSize();
}

Title& Title::operator=(const Title& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
    _size       = obj.getSize();
    return *this;
}

Title::~Title() {
    _widget.clear();
}


void                   Title::setSize(const Title::SIZE& size) { _size = size;      }
void                   Title::addWidget(IInlinable* widget)    { _widget << widget; }
Title::SIZE            Title::getSize()                  const { return _size;      }
QList<IInlinable*>     Title::getWidget()                const { return _widget;    }

QString                Title::render()                   const {
    QString res;
    QMap<Title::SIZE, QString> title;
    title[TITLE1] = "h1";
    title[TITLE2] = "h2";
    title[TITLE3] = "h3";
    title[TITLE4] = "h4";
    title[TITLE5] = "h5";
    title[TITLE6] = "h6";

    if (!_widget.isEmpty()) {
        res.append("<" + title[_size] + renderAttribute() + ">");
        for (QList<IInlinable*>::const_iterator it = _widget.begin(); it != _widget.end(); ++it) {
            res.append((*it)->render());
        }
        res.append("</" + title[_size] + ">\n");
    }
    return res;
}

} // namespace UI

