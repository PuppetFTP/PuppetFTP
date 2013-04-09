#ifndef TITLE_H
#define TITLE_H

#include "AbstractWidget.h"
#include "IInlinable.h"

namespace UI {

class Title : public AbstractWidget {
public:
    enum SIZE { TITLE1, TITLE2, TITLE3, TITLE4, TITLE5, TITLE6 };
protected:
    SIZE               _size;
    QList<IInlinable*> _widget;

public:
    Title(const SIZE& size = TITLE1);
    Title(const QString& title, const SIZE& size = TITLE1);
    Title(IInlinable* widget, const SIZE& size = TITLE1);
    Title(const Title& obj);
    Title& operator=(const Title& obj);
    virtual ~Title();

    void                   setSize(const SIZE& size);
    void                   addWidget(IInlinable* widget);
    SIZE                   getSize()   const;
    QList<IInlinable*>     getWidget() const;
    QString                render()    const;
};

} // namespace UI

#endif // TITLE_H
