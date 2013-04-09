#ifndef FORM_H
#define FORM_H

#include <QString>
#include <QMap>
#include <QVariant>
#include <QStringList>
#include "AbstractWidget.h"
#include "Title.h"
#include "IWidgetForm.h"

namespace UI {

class Form : public AbstractWidget {
public:
    enum RENDERING_MODE { LIST, TABLE, NONE };
    enum SEND_METHOD    { POST, GET };
    enum ENCTYPE        { URLENCODED, MULTIPART };

protected:
    SEND_METHOD                                    _method;
    ENCTYPE                                        _enctype;
    RENDERING_MODE                                 _rendering;
    bool                                           _isRendererLabel;
    QMap<QString, QStringList>                     _widgetOrder;
    QList<IWidgetForm*>                            _widgetSchema;
    QStringList                                    _sectionOrder;
    QMap<QString, Title*>                          _section;

public:
    Form();
    Form(const QString& action);
    virtual ~Form();

    virtual SEND_METHOD                                    getMethod()                             const;
    virtual ENCTYPE                                        getEnctype()                            const;
    virtual QString                                        getAction()                             const;
    virtual RENDERING_MODE                                 getRendering()                          const;
    virtual bool                                           isRendererLabel()                       const;
    virtual IWidgetForm*                                   getWidget(const QString& field)         const;
    virtual QList<IWidgetForm*>                            getWidgets()                            const;
    virtual Title*                                         getSection(const QString& section)      const;
    virtual QMap<QString, Title*>                          getSections()                           const;

    virtual void                                           setAction(const QString& action);
    virtual void                                           setMethod(const SEND_METHOD& method);
    virtual void                                           setEnctype(const ENCTYPE& enctype);
    virtual void                                           setRendering(const RENDERING_MODE& rendering);
    virtual void                                           setRendererLabel(const bool& rendererLabel);
    virtual void                                           disabledForm();

    virtual void                                           addWidget(const QString& name, IWidgetForm* value);
    virtual void                                           addSection(const QString& section, const QString& name);
    virtual void                                           removeWidget(const QString& name);
    virtual void                                           removeAllWidgets();
    virtual void                                           removeSection(const QString& section);
    virtual void                                           removeAllSections();

    virtual QMap<QString, QStringList>                     getFieldOrder() const;
    virtual QStringList                                    getSectionOrder() const;
    virtual QStringList                                    getFieldOrder(const QString& section) const;
    virtual void                                           setFieldOrder(const QString& section, const QStringList& order);
    virtual void                                           setSectionOrder(const QStringList& order);

    virtual void                                           bind(const QMap<QString, QVariant>& values);
    virtual bool                                           validate() const;
    virtual QString                                        render() const;
};

} // namespace UI

#endif // FORM_H
