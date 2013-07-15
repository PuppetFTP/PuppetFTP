#include "Information.h"
#include "Text.h"

namespace UI {

Information::Information() {
}


Information::Information(const QString& text, const TYPE& type, const EVENT& event) :
    _text(text), _type(type), _event(event) {
}

Information::~Information() {
}

void                Information::setText(const QString& text, const TYPE& type, const EVENT& event) {
    _text  = text;
    _type  = type;
    _event = event;
}

void                Information::setType(const TYPE& type)    { _type = type;   }
void                Information::setEvent(const EVENT& event) { _event = event; }
QString             Information::getText()              const { return _text;   }
Information::TYPE   Information::getType()              const { return _type;   }
Information::EVENT  Information::getEvent()             const { return _event;  }

QString Information::render() const {
    Text* text = new Text(_text);
    text->setAttribute("id", "information");
    if (_type == TOOLTIP)
        text->setAttribute("class", "tooltip");
    return text->render();
}

}
