/*
 * AbstractFormWidget.cpp
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#include "AbstractWidget.h"


namespace UI {

AbstractWidget::AbstractWidget() {
}

AbstractWidget::~AbstractWidget() {
    removeAllAttributes();
}

  //QVariant AbstractWidget::getValue()                        const                 { return _value;                }
QString  AbstractWidget::getAttribute(const QString& name) const                 { return _attributes[name];     }
QMap<QString, QString>  AbstractWidget::getAttributes()    const                 { return _attributes;           }
QString  AbstractWidget::getId()                           const                 { return getAttribute("id");    }
QString  AbstractWidget::getClasses()                      const                 { return getAttribute("class"); }

  //void     AbstractWidget::setValue(const QVariant& value)                         { _value = value;                }
void     AbstractWidget::setAttribute(const QString& name, const QString& value) { _attributes[name] = value;     }
void     AbstractWidget::removeAttribute(const QString& name)                    { _attributes.remove(name);      }
void     AbstractWidget::removeAllAttributes()                                   { _attributes.clear();           }
void     AbstractWidget::setId(const QString& id)                                { setAttribute("id", id);        }

void     AbstractWidget::addClass(const QString& className) {
    if (_attributes.contains("class"))
        _attributes["class"].append(" ");
    _attributes["class"].append(className);
}

QString  AbstractWidget::renderAttribute() const {
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

QString  AbstractWidget::render(const QMap<QString, QString>& attributes) {
    for (QMap<QString, QString>::const_iterator it = attributes.begin(); it != attributes.end(); it++) {
        _attributes[it.key()] = it.value();
    }
    return render();
}

} // namespace Widget
