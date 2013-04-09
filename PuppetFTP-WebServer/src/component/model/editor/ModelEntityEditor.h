/*
 * EntityBaseForm.h
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#ifndef MODELENTITYEDITOR_H
#define MODELENTITYEDITOR_H

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMap>
#include <QString>
#include <QVariant>
#include "IModelEditor.h"
#include "Widget.h"
#include <QDebug>

namespace UI {

typedef QString (*fnctFormat)(const QVariant&);

template <typename E>
class ModelEntityEditor : public IModelEditor {
protected:
    Container*                _content;
    Form*                     _form;
    QMap<QString, fnctFormat> _format;

public:
    ModelEntityEditor() {
        _form    = new Form();
        for (int i = 0; i < E::staticMetaObject.propertyCount(); i++) {
            QMetaProperty field = E::staticMetaObject.property(i);
            if (QString(field.name()) != "objectName") {
                if (field.type() == QVariant::Bool) {
                    InputChoice* boolean = new InputChoice(field.name(), InputChoice::CHECKBOX);
                    boolean->addOption("1", "");
                    boolean->setLabel(field.name());
                    _form->addWidget("editor", boolean);
                } else if (field.type() == QVariant::UserType) {
//                    QMetaEnum test = field.enumerator();
//                    qDebug() << "Is Enummmm: " <<  test.name();

                    InputChoice* select = new InputChoice(field.name(), InputChoice::SELECT);

//                    select->addOption("0", "false");
//                    select->addOption("1", "true");
//                    select->setLabel(field.name());
                    _form->addWidget("editor", select);
                } else {
                    Input* input = new Input(field.name());
                    input->setLabel(field.name());
                    _form->addWidget("editor", input);
                }
            }
        }
        Input* submit = new Input("submit", Input::SUBMIT);
        submit->setValue("Save");
        _form->addWidget("submit", submit);

        _content = new Container();
        _content->addClass("box");
        _content->addWidget(_form);
    }

    virtual ~ModelEntityEditor() {
        delete _content;
    }

    virtual void bind(QObject* entity) {
        bind(dynamic_cast<E*>(entity));
    }

    virtual void bind(const E* entity) {
        if (entity == 0) return;
        for (int i = 0; i < E::staticMetaObject.propertyCount(); i++) {
            QMetaProperty field = E::staticMetaObject.property(i);
            if (QString(field.name()) != "objectName") {
                QVariant v = field.read(entity);
                if (v.isValid()) {
                    IWidgetForm* widget = _form->getWidget(field.name());
                    if (widget != 0) {
                        if (_format.contains(field.name())) {
                            v = _format[field.name()](v);
                        }
                        widget->setValue(v);
                    }
                }
            }
        }
    }

    void setFormat(const QString& property, const fnctFormat& fnct) {
        _format[property] = fnct;
    }

    virtual Form*       getForm()    const { return _form;    }
    virtual Container*  getContent() const { return _content; }
};

} // namespace UI

#endif // MODELENTITYEDITOR_H
