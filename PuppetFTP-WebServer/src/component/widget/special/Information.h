#ifndef INFORMATION_H
#define INFORMATION_H

#include "AbstractWidget.h"

namespace UI {

class Information: public AbstractWidget {
public:
    enum TYPE { TOOLTIP, NONE };
    enum EVENT { CLICK, HOVER, MOUSEDOWN, MOUSEUP };

protected:
    QString _text;
    TYPE    _type;
    EVENT   _event;

public:
    Information();
    Information(const QString& text, const TYPE& type = TOOLTIP, const EVENT& event = HOVER);
    ~Information();

    void    setText(const QString& text, const TYPE& type = TOOLTIP, const EVENT& event = HOVER);
    void    setType(const TYPE& type);
    void    setEvent(const EVENT& event);

    QString getText()  const;
    TYPE    getType()  const;
    EVENT   getEvent() const;

    QString render()   const;
};

}

#endif // INFORMATION_H
