/*
 * Textare.h
 *
 *  Created on: 02 nov. 2012
 *      Author: mtonnelier
 */

#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "AbstractWidgetForm.h"

namespace UI {

class Textarea : public AbstractWidgetForm {
private:
    Textarea();
public:
    Textarea(const QString& name);
    virtual ~Textarea();

    void    setRows(const QString& rows);
    void    setCols(const QString& cols);
    QString getRows() const;
    QString getCols() const;

    QString render()  const;
};

} // namespace UI

#endif // TEXTAREA_H
