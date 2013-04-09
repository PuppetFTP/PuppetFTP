/*
 * AbstractWidget.h
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#ifndef ABSTRACTWIDGET_H_
#define ABSTRACTWIDGET_H_

#include <QString>
#include <QMap>
#include <QVariant>
#include "IWidget.h"


namespace UI {

class AbstractWidget : public IWidget {
protected:
    QMap<QString, QString> _attributes;

public:
    AbstractWidget();
    virtual ~AbstractWidget();

    virtual QString  getAttribute(const QString& name) const;
    virtual QMap<QString, QString>  getAttributes()    const;
    virtual QString  getId()                           const;
    virtual QString  getClasses()                      const;

    virtual void     setAttribute(const QString& name, const QString& value);
    virtual void     setId(const QString& id);
    virtual void     addClass(const QString& className);

    virtual void     removeAttribute(const QString& name);
    virtual void     removeAllAttributes();

    virtual QString  render(const QMap<QString, QString>& attributes);
    virtual QString  render() const = 0;

protected:
    virtual QString  renderAttribute() const;
};

} // namespace UI

#endif /* ABSTRACTWIDGET_H_ */
