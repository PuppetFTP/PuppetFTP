/*
 * Textarea.cpp
 *
 *  Created on: 02 nov. 2012
 *      Author: mtonnelier
 */

#include "Textarea.h"

namespace UI {

Textarea::Textarea() :
    AbstractWidgetForm("") {
}

Textarea::Textarea(const QString& name) :
    AbstractWidgetForm(name) {
    setId(name);
    setRows("5");
    setCols("50");
}

Textarea::~Textarea() {
}

void    Textarea::setRows(const QString& rows) { setAttribute("rows", rows);  }
void    Textarea::setCols(const QString& cols) { setAttribute("cols", cols);  }
QString Textarea::getRows()              const { return getAttribute("rows"); }
QString Textarea::getCols()              const { return getAttribute("cols"); }

QString Textarea::render() const {
    return "<textarea" + renderAttribute() + " name=\"" + _name + "\">" + _value.toString() + "</texarea>";
}

} // !namespace UI
