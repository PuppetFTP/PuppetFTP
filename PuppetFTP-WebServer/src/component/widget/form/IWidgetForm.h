/*
 * IWidgetForm.h
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#ifndef IWIDGETFORM_H_
#define IWIDGETFORM_H_

#include "IWidget.h"
#include "IInlinable.h"

namespace UI {

class IWidgetForm : public IWidget {
public:
    virtual ~IWidgetForm() {}

    virtual void        setName(const QString& name)                            = 0;
    virtual void        setLabel(const QString& label)                          = 0;
    virtual void 	    setHelp(const QString& help)                            = 0;
    virtual void        setValue(const QVariant& value)                         = 0;
    virtual void        setAttribute(const QString& name, const QString& value) = 0;
    virtual void        setId(const QString& id)                                = 0;
    virtual void        addClass(const QString& className)                      = 0;
    virtual void        removeAttribute(const QString& name)                    = 0;
    virtual void        removeAllAttributes()                                   = 0;

    virtual QString     getName()                         const                 = 0;
    virtual IWidget*    getLabel()                        const                 = 0;
    virtual IWidget*    getHelp()                         const                 = 0;
    virtual QVariant    getValue()                        const                 = 0;
    virtual QString     getAttribute(const QString& name) const                 = 0;
    virtual QString     getId()                           const                 = 0;
    virtual QString     getClasses()                      const                 = 0;

    virtual QString     renderLabel()                     const                 = 0;
    virtual QString     renderHelp()                      const                 = 0;
    virtual QString     render()                          const                 = 0;
};

} // namespace UI

#endif /* IWIDGETFORM_H_ */
