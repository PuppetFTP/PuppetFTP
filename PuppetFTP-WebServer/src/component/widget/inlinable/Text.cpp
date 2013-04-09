/*
 * Text.cpp
 *
 *  Created on: 05 nov. 2012
 *      Author: mtonnelier
 */

#include "Text.h"

namespace UI {

Text::Text(const QString& text) :
    _text(text) {
}

Text::Text(const Text& obj) {
    _attributes = obj.getAttributes();
}

Text& Text::operator=(const Text& obj) {
    _attributes = obj.getAttributes();
    return *this;
}

Text::~Text() {
}

void    Text::setText(const QString& text) { _text = text; }
QString Text::getText()              const { return _text;  }

QString Text::render()               const {
    QString res;

    if (!_attributes.empty()) {
        res.append("<span"+renderAttribute()+">");
    }

    res.append(_text);

    if (!_attributes.empty()) {
        res.append("</span>");
    }

    return res;
}

} // !namespace UI
