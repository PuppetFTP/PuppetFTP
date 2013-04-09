#include "List.h"

namespace UI {

List::List(const List::MODE& mode) :
    _mode(mode) {
}

List::List(const List& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
    _mode       = obj.getNodeMode();
}

List& List::operator=(const List& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
    _mode       = obj.getNodeMode();
    return *this;
}

List::~List() {
    for (QList<Container*>::iterator it = _widget.begin(); it != _widget.end(); ++it) {
        delete (*it);
    }
    _widget.clear();
}

void              List::addWidget(Container* widget)  {
    widget->setNodeType(Container::NONE);
    _widget.push_back(widget);
}

void              List::setNodeMode(const List::MODE& mode) { _mode = mode;   }
List::MODE        List::getNodeMode()                 const { return _mode;   }
QList<Container*> List::getWidget()                   const { return _widget; }

QString List::render() const {
    QString res;

    QMap<List::MODE, QString> list;
    list[List::ORDERER]   = "ol";
    list[List::UNORDERER] = "ul";

    res.append("<"+list[_mode] + renderAttribute() + ">\n");

    for (QList<Container*>::const_iterator it = _widget.begin(); it != _widget.end(); ++it) {
        res.append("<li>");
        res.append((*it)->render());
        res.append("</li>");
    }
    res.append("</"+list[_mode]+">\n");
    return res;
}


} // namespace UI


