#include "InputChoice.h"

namespace UI {

InputChoice::InputChoice() :
    AbstractWidgetForm("") {
    _type  = InputChoice::RADIO;
}

InputChoice::InputChoice(const QString& name, const InputChoice::TYPE& type) :
    AbstractWidgetForm(name) {
    addClass(name);
    _type  = type;
}

InputChoice::~InputChoice() {
}

void              InputChoice::setType(const TYPE& type)                            { _type = type;                      }
InputChoice::TYPE InputChoice::getType()                                      const { return _type;                      }
void              InputChoice::addOption(const QString& key, const QString& value)  { _options.insert(key, value);       }
void              InputChoice::addChecked(const QString& value)                     { _checkedList.append(value);        }
void              InputChoice::removeOption(const QString& key)                     { _options.remove(key);              }
void              InputChoice::removeChecked(const QString& value)                  { _checkedList.removeAll(value);     }
void              InputChoice::setValue(const QVariant& value) {
    _value = value;
    addChecked(value.toString());
}

QString           InputChoice::render() const {
    QString res;
    QMap<InputChoice::TYPE, QString> input;
    input[InputChoice::RADIO]    = "radio";
    input[InputChoice::CHECKBOX] = "checkbox";

    if (_type == InputChoice::SELECT) {
        res.append("<select" + renderAttribute() + " name=\"" + _name + "\">\n");
    }
    for (QMap<QString, QString>::const_iterator it = _options.begin(); it != _options.end(); it++) {
        if (_type == InputChoice::SELECT) {
            res.append("<option value=\""+it.key()+"\"");
            if (_checkedList.contains(it.key()))
                res.append(" selected=\"selected\"");
            res.append(">");
        } else {
            res.append("<input id=\"" + _name + "-" + it.key() + "\"" + renderAttribute() + " type=\""+input[_type]+"\" name=\"" + _name + "\" value=\"" + it.key() + "\"");
            if (_checkedList.contains(it.key()))
                res.append(" checked=\"checked\"");
            res.append(" /> ");
        }

        res.append(it.value());

        if (_type == InputChoice::SELECT) {
            res.append("</option>");
        }
        res.append("\n");
    }
    if (_type == InputChoice::SELECT) {
        res.append("</select>\n");
    }
    return res;
}

} // !namespace UI
