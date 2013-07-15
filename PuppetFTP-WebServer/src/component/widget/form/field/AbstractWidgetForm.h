/*
 * AbstractWidgetForm.h
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#ifndef ABSTRACTWIDGETFORM_H_
#define ABSTRACTWIDGETFORM_H_

#include <QString>
#include <QMap>
#include <QVariant>
#include "IWidgetForm.h"
#include "IInlinable.h"
#include "Information.h"

namespace UI {

class AbstractWidgetForm : public IWidgetForm {
protected:
    QString                _name; // id will be equal to name, must be unique
    IWidget*               _label;
    Information*           _help;
    QVariant               _value;
    QMap<QString, QString> _attributes;

public:
    AbstractWidgetForm(const QString& name);
    virtual ~AbstractWidgetForm();

    virtual QString     getName()                         const;
    virtual IWidget*    getLabel()                        const;
    virtual IWidget*    getHelp()                         const;
    virtual QVariant    getValue()                        const;
    virtual QString     getAttribute(const QString& name) const;
    virtual QString     getId()                           const;
    virtual QString     getClasses()                      const;

    virtual void       setName(const QString& name);
    virtual void       setLabel(const QString& label);
    virtual void       setHelp(const QString& help);
    virtual void       setValue(const QVariant& value);
    virtual void       setAttribute(const QString& name, const QString& value);
    virtual void       setId(const QString& id);
    virtual void       addClass(const QString& className);

    virtual void       removeAttribute(const QString& name);
    virtual void       removeAllAttributes();

    virtual QString    renderLabel()                     const;
    virtual QString    renderHelp()                      const;
protected:
    virtual QString  renderAttribute() const;
};

} // namespace UI

#endif /* ABSTRACTWIDGETFORM_H_ */
