#ifndef INPUT_H
#define INPUT_H

#include "AbstractWidgetForm.h"

namespace UI {

class Input : public AbstractWidgetForm {
public:
    enum TYPE { TEXT, SUBMIT, PASSWORD, HIDDEN, BUTTON };
protected:
    bool    _isPlaceholder;
    TYPE    _type;

private:
    Input();
public:
    Input(const QString& name, const TYPE& type = TEXT);
    virtual ~Input();

    void    setType(const TYPE& type);
    void    setPlaceholder(const bool& placeholder);
    bool    isPlaceholder() const;
    TYPE    getType()       const;

    QString render() const;
};

} // namespace UI

#endif // INPUT_H
