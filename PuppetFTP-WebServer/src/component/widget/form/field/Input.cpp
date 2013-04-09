#include "Input.h"

namespace UI {

Input::Input() :
    AbstractWidgetForm("") {
    _type          = Input::TEXT;
    _isPlaceholder = false;
}

Input::Input(const QString& name, const Input::TYPE& type) :
    AbstractWidgetForm(name) {
    _type          = type;
    _isPlaceholder = false;
    setId(name);
}

Input::~Input() {
}

void        Input::setPlaceholder(const bool& placeholder) { _isPlaceholder = placeholder; }
void        Input::setType(const TYPE& type)               { _type = type;                 }

bool        Input::isPlaceholder()                   const { return _isPlaceholder;        }
Input::TYPE Input::getType()                         const { return _type;                 }

QString Input::render() const {
    QString res;
    QMap<Input::TYPE, QString> input;
    input[Input::TEXT]     = "text";
    input[Input::SUBMIT]   = "submit";
    input[Input::PASSWORD] = "password";
    input[Input::HIDDEN]   = "hidden";
    input[Input::BUTTON]   = "button";

    res.append("<input" + renderAttribute() + " type=\""+input[_type]+"\" name=\"" + _name + "\"");
    if (!_value.toString().isEmpty())
        res.append(" value=\"" + _value.toString() + "\"");
    if (_isPlaceholder == true)
        res.append(" placeholder=\"" + getLabel()->render() + "\"");
    res.append(" />");
    return res;
}

} // !namespace UI
