/*
 * Container.cpp
 *
 *  Created on: 10 nov. 2012
 *      Author: mtonnelier
 */
#include "Container.h"
#include "Title.h"

namespace UI {

Container::Container(const Container::TYPE& type) :
    _type(type) {
}

Container::Container(const QString& title, const Container::TYPE& type) :
    _type(type) {
    _widget.push_back(new Title(title));
}

Container::Container(const Container& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
    _type       = obj.getNodeType();
}

Container& Container::operator=(const Container& obj) {
    _widget     = obj.getWidget();
    _attributes = obj.getAttributes();
    _type       = obj.getNodeType();
    return *this;
}

Container::~Container() {
}

void            Container::setNodeType(const Container::TYPE& type) { _type = type;               }
void            Container::addFirstWidget(IWidget* widget)          { if (widget != NULL) _widget.push_front(widget); }
void            Container::addWidget(IWidget* widget)               { if (widget != NULL) _widget.push_back(widget);  }
Container::TYPE Container::getNodeType()                      const { return _type;               }
QList<IWidget*> Container::getWidget()                        const { return _widget;             }

QString Container::render() const {
    QString res;
    QMap<Container::TYPE, QString> block;
    block[Container::DIV]        = "div";
    block[Container::SECTION]    = "section";
    block[Container::ASIDE]      = "aside";
    block[Container::HEADER]     = "header";
    block[Container::FOOTER]     = "footer";
    block[Container::NAV]        = "nav";
    block[Container::PARAGRAPH]  = "p";
    block[Container::NONE]       = "div";

    if (_type != Container::NONE || (_type == Container::NONE && !_attributes.empty())) {
        res.append("<" + block[_type] + renderAttribute() + ">\n");
    }

    for (QList<IWidget*>::const_iterator it = _widget.begin(); it != _widget.end(); ++it) {
        res.append((*it)->render());
    }

    if (_type != Container::NONE || (_type == Container::NONE && !_attributes.empty())) {
        res.append("</" + block[_type] + ">\n");
    }
    return res;
}


} // namespace UI
