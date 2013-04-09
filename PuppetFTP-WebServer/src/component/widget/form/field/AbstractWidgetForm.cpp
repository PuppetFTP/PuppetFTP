/*
 * AbstractWidgetForm.cpp
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#include "AbstractWidgetForm.h"
#include "Text.h"

namespace UI {

AbstractWidgetForm::AbstractWidgetForm(const QString& name) :
    _name(name) {
    _label = NULL;
    _help  = NULL;
}

AbstractWidgetForm::~AbstractWidgetForm() {
    removeAllAttributes();
//    delete _label;
//    delete _help;
}

QString     AbstractWidgetForm::getName()                         const                 { return _name;                     }
IWidget*    AbstractWidgetForm::getLabel()                        const                 { return _label;                    }
IWidget*    AbstractWidgetForm::getHelp()                         const                 { return _help;                     }
QVariant    AbstractWidgetForm::getValue()                        const                 { return _value;                    }
QString     AbstractWidgetForm::getAttribute(const QString& name) const                 { return _attributes[name];         }
QString     AbstractWidgetForm::getId()                           const                 { return getAttribute("id");        }
QString     AbstractWidgetForm::getClasses()                      const                 { return getAttribute("class");     }

void        AbstractWidgetForm::setName(const QString& name)                            { _name  = name;                    }
void        AbstractWidgetForm::setLabel(const QString& label)                          { _label = new Text(label);         }
void        AbstractWidgetForm::setHelp(const QString& help)                            { _help  = new Text(help);          }
void        AbstractWidgetForm::setValue(const QVariant& value)                         { _value = value;                   }
void        AbstractWidgetForm::setAttribute(const QString& name, const QString& value) { _attributes[name] = value;        }
void        AbstractWidgetForm::removeAttribute(const QString& name)                    { _attributes.remove(name);         }
void        AbstractWidgetForm::removeAllAttributes()                                   { _attributes.clear();              }
void        AbstractWidgetForm::setId(const QString& id)                                { setAttribute("id", id);           }

void        AbstractWidgetForm::addClass(const QString& className) {
    if (_attributes.contains("class"))
        _attributes["class"].append(" ");
    _attributes["class"].append(className);
}

QString     AbstractWidgetForm::renderLabel() const {
    return _label->render();
}

QString     AbstractWidgetForm::renderHelp() const {
    return _help->render();
}

QString     AbstractWidgetForm::renderAttribute() const {
    QString res;
    for (QMap<QString, QString>::const_iterator it = _attributes.begin(); it != _attributes.end(); ++it) {
        res.append(" ");
        res.append(it.key());
        if (!it.value().isEmpty()){
            res.append("=\"");
            res.append(it.value());
            res.append("\"");
        }
    }
    return res;
}

} // !namespace UI
