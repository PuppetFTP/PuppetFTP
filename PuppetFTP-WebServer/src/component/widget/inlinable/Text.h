#ifndef TEXT_H
#define TEXT_H

#include <QVariant>
#include "AbstractWidget.h"
#include "IInlinable.h"

namespace UI {

class Text : public AbstractWidget, public IInlinable {
protected:
    QString _text;
public:
    Text(const QString& text);
    Text(const Text& obj);
    Text& operator=(const Text& obj);
    virtual ~Text();

    void            setText(const QString& text);
    QString         getText() const;
    QString         render()   const;
};

} // namespace UI

#endif // TEXT_H
