#include "Form.h"
#include "Table.h"
#include "List.h"
#include <QDebug>

namespace UI {

Form::Form() {
    _isRendererLabel = true;
    _rendering       = TABLE;
    setMethod(Form::POST);
    setEnctype(Form::URLENCODED);
}

Form::Form(const QString& action) {
    setAction(action);
    _isRendererLabel = true;
    _rendering       = TABLE;
    setMethod(Form::POST);
    setEnctype(Form::URLENCODED);
}

Form::~Form() {
    removeAllSections();
    removeAllWidgets();
}

QString                                        Form::getAction()                             const                                 { return getAttribute("action");    }
Form::SEND_METHOD                              Form::getMethod()                             const                                 { return _method;                   }
Form::ENCTYPE                                  Form::getEnctype()                            const                                 { return _enctype;                  }
Form::RENDERING_MODE                           Form::getRendering()                          const                                 { return _rendering;                }
bool                                           Form::isRendererLabel()                       const                                 { return _isRendererLabel;          }

IWidgetForm*                                   Form::getWidget(const QString& name) const {
    for (QList<IWidgetForm*>::const_iterator it = _widgetSchema.begin(); it != _widgetSchema.end(); it++) {
        if ((*it)->getName() == name)
            return (*it);
    }
    return NULL;
}

QList<IWidgetForm*>                            Form::getWidgets()                            const                                 { return _widgetSchema;             }
Title*                                         Form::getSection(const QString& section)      const                                 { return _section[section];         }
QMap<QString, Title*>                          Form::getSections()                           const                                 { return _section;                  }
void                                           Form::setAction(const QString& action)                                              { setAttribute("action", action);   }

void                                           Form::setMethod(const Form::SEND_METHOD& method) {
    _method = method;
    setAttribute("method", (_method == Form::POST ? "post" : "get"));
}

void                                           Form::setEnctype(const Form::ENCTYPE& enctype) {
    _enctype = enctype;
    if (_enctype == Form::MULTIPART)
        setAttribute("enctype", "multipart/form-data");
}

void                                           Form::setRendering(const Form::RENDERING_MODE& rendering)                           { _rendering = rendering;           }
void                                           Form::setRendererLabel(const bool& rendererLabel)                                   { _isRendererLabel = rendererLabel; }

void                                           Form::disabledForm()                                                                {
    for (QList<IWidgetForm*>::iterator it = _widgetSchema.begin(); it != _widgetSchema.end(); it++) {
        (*it)->setAttribute("disabled", "disabled");
    }
}

void                                           Form::addSection(const QString& section, const QString& name)                       {
    _section[section] = new Title(name);
    if (_sectionOrder.contains(section))
        _sectionOrder.removeAll(section);
    _sectionOrder << section;
}

void                                           Form::addWidget(const QString& section, IWidgetForm* value) {
    for (QList<IWidgetForm*>::iterator it = _widgetSchema.begin(); it != _widgetSchema.end(); it++) {
        if ((*it)->getName() == value->getName()) {
            delete (*it);
        }
    }

    for (QMap<QString, QStringList>::iterator it = _widgetOrder.begin(); it != _widgetOrder.end(); it++) {
        if ((it.value()).contains(value->getName())) {
            (it.value()).removeAll(value->getName());
        }
    }
    _widgetSchema << value;
    _widgetOrder[section] << value->getName();
    if (!_sectionOrder.contains(section))
        addSection(section, "");
}

void                                           Form::removeWidget(const QString& name) {
    for (QList<IWidgetForm*>::iterator it = _widgetSchema.begin(); it != _widgetSchema.end(); it++) {
        if ((*it)->getName() == name) {
            delete (*it);
            _widgetSchema.removeAll((*it));
            _widgetOrder.remove(name);
        }
    }
}

void                                           Form::removeAllWidgets()                                                            { _widgetSchema.clear();            }

void                                           Form::removeSection(const QString& section) {
    if (_section.contains(section)) {
        delete _section[section];
        _section.remove(section);
        _sectionOrder.removeAll(section);
    }
}

void                                           Form::removeAllSections() {
    for (QMap<QString, Title*>::iterator it = _section.begin(); it != _section.end(); it++) {
        delete it.value();
        _sectionOrder.removeAll(it.key());
    }
    _section.clear();
}


QMap<QString, QStringList>                     Form::getFieldOrder()                        const { return _widgetOrder;          }
QStringList                                    Form::getFieldOrder(const QString& section)  const { return _widgetOrder[section]; }
QStringList                                    Form::getSectionOrder()                      const { return _sectionOrder;         }

void                                           Form::setFieldOrder(const QString& section, const QStringList& order) {
    _widgetOrder[section].clear();
    _widgetOrder[section].append(order);
}

void                                           Form::setSectionOrder(const QStringList& order) {
    _sectionOrder.clear();
    _sectionOrder.append(order);
}

void                                           Form::bind(const QMap<QString, QVariant>& values) {
    for (QMap<QString, QVariant>::const_iterator it = values.begin(); it != values.end(); it++) {
        for (QList<IWidgetForm*>::iterator widget = _widgetSchema.begin(); widget != _widgetSchema.end(); widget++) {
            if (it.key() == (*widget)->getName()) {
                (*widget)->setValue(it.value());
            }
        }
    }
}

bool                                           Form::validate() const {
    return true;
}

QString                                        Form::render() const {
    QString res;

    res.append("<form" + renderAttribute() + ">\n");

    for (QStringList::const_iterator sectionName = _sectionOrder.begin(); sectionName != _sectionOrder.end(); sectionName++) {
        Table*     table = new Table();
        List*      list  = new List();
        Container* div   = new Container(UI::Container::NONE);
        res.append(_section[(*sectionName)]->render());
        for (QStringList::const_iterator widgetName = _widgetOrder[(*sectionName)].begin(); widgetName != _widgetOrder[(*sectionName)].end(); widgetName++) {
            for (QList<IWidgetForm*>::const_iterator widget = _widgetSchema.begin(); widget != _widgetSchema.end(); widget++) {
                if ((*widget)->getName() == (*widgetName)) {
                    Container* label     = new Container(Container::NONE);
                    Container* container = new Container(Container::NONE);

                    if (_rendering == Form::TABLE) {
                        QList<Container*> row;
                        if (_isRendererLabel == true && (*widget)->getLabel() != NULL) {
                            label->addWidget((*widget)->getLabel());
                            row << label;
                        }

                        container->addWidget((*widget));
                        row << container;

                        table->addRow(row);

                    } else if (_rendering == Form::LIST) {

                        if (_isRendererLabel == true && (*widget)->getLabel() != NULL) {
                            label->addWidget((*widget)->getLabel());
                            list->addWidget(label);
                        }

                        container->addWidget((*widget));
                        list->addWidget(container);
                    } else if (_rendering == Form::NONE) {

                        if (_isRendererLabel == true && (*widget)->getLabel() != NULL) {
                            label->addWidget((*widget)->getLabel());
                            div->addWidget(label);
                        }

                        container->addWidget((*widget));
                        div->addWidget(container);
                    }
                }
            }
        }
        if (_rendering == Form::TABLE) {
            res.append(table->render());
        } else if (_rendering == Form::LIST) {
            res.append(list->render());
        } else if (_rendering == Form::NONE) {
            res.append(div->render());
        }
        delete table;
        delete list;
        delete div;
    }
    res.append("</form>\n");
    return res;
}

} // namespace UI
