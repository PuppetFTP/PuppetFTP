/*
 * IWidget.h
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#ifndef IWIDGET_H_
#define IWIDGET_H_

#include <QVariant>

namespace UI {

class IWidget {
public:
    virtual ~IWidget() {}

    virtual QString  getAttribute(const QString& name) const                 = 0;
    virtual QString  getId()                           const                 = 0;
    virtual QString  getClasses()                      const                 = 0;

    virtual void     setAttribute(const QString& name, const QString& value) = 0;
    virtual void     setId(const QString& id)                                = 0;
    virtual void     addClass(const QString& className)                      = 0;

    virtual void     removeAttribute(const QString& name)                    = 0;
    virtual void     removeAllAttributes()                                   = 0;

    virtual QString  render() const                                          = 0;
};

} // namespace UI

#endif /* IWIDGET_H_ */
