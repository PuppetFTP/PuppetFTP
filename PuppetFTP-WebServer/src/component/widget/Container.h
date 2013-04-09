#ifndef CONTAINER_H
#define CONTAINER_H

#include "AbstractWidget.h"
#include "IInlinable.h"

namespace UI {

class Container : public AbstractWidget {
public:
    enum TYPE { DIV, SECTION, ASIDE, HEADER, FOOTER, NAV, PARAGRAPH, NONE };
protected:
    TYPE                _type;
    QList<IWidget*>     _widget;

public:
    Container(const TYPE& type = DIV);
    Container(const QString& id, const TYPE& type = DIV);
    Container(const Container& obj);
    Container& operator=(const Container& obj);
    virtual ~Container();

    void            setNodeType(const TYPE& type);
    void            addFirstWidget(IWidget* widget);
    void            addWidget(IWidget* widget);
    TYPE            getNodeType() const;
    QList<IWidget*> getWidget()   const;
    QString         render()      const;
};

} // namespace UI

#endif // CONTAINER_H
