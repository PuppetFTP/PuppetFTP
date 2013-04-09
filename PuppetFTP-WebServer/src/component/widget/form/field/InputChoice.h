#ifndef InputChoiceLIST_H
#define InputChoiceLIST_H

#include "AbstractWidgetForm.h"

namespace UI {

class InputChoice : public AbstractWidgetForm {
public:
    enum TYPE { RADIO, CHECKBOX, SELECT };
protected:
    TYPE                   _type;
    QMap<QString, QString> _options;
    QList<QString>         _checkedList;

private:
    InputChoice();
public:
    InputChoice(const QString& name, const TYPE& type = RADIO);
    virtual ~InputChoice();

    void    setType(const TYPE& type);
    void    addOption(const QString& key, const QString& value);
    void    addChecked(const QString& value);
    void    removeOption(const QString& key);
    void    removeChecked(const QString& value);
    void    setValue(const QVariant& value);
    TYPE    getType() const;

    QString render() const;
};

}


#endif // InputChoiceLIST_H
