#ifndef LIST_H
#define LIST_H

#include "AbstractWidget.h"
#include "Container.h"

namespace UI {

class List : public AbstractWidget {
public:
    enum MODE { ORDERER, UNORDERER };
protected:
    MODE                _mode;
    QList<Container*>   _widget;

public:
    List(const MODE& mode = UNORDERER);
    List(const List& obj);
    List& operator=(const List& obj);
    virtual ~List();

    void              setNodeMode(const MODE& mode);
    void              addWidget(Container* widget);
    MODE              getNodeMode() const;
    QList<Container*> getWidget()   const;
    QString           render()      const;
};

} // namespace UI

#endif // LIST_H
