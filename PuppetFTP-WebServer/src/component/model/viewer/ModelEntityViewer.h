/*
 * EntityBaseViewer.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef MODELENTITYVIEWER_H
#define MODELENTITYVIEWER_H

#include <QMetaProperty>
#include <QString>
#include <QStringList>
#include <QMap>
#include "IModelViewer.h"
#include "Container.h"
#include "IWidget.h"
#include "Title.h"
#include "Table.h"
#include "Text.h"


namespace UI {

template<class E>
class ModelEntityViewer : public IModelViewer, private Container {
private:
    Container*                  _content;
    QStringList                 _titleProperties;
    QStringList                 _displayOrder;
    QStringList                 _properties;
    QMap<QString, QString>      _labels;
    QMap<QString, IWidget*>     _propertiesWidgets;
    UI::Title*                  _title;

public:
    ModelEntityViewer() : _title(0) {
        _content = new Container();
        _content->setId("details");
        for (int i = 0; i < E::staticMetaObject.propertyCount(); i++) {
            QMetaProperty field = E::staticMetaObject.property(i);
            if (QString(field.name()) != "objectName") {
                addProperty(field.name());
            }
        }
    }

    virtual ~ModelEntityViewer() {
    }

    virtual void fill(QObject* entity) {
        fill(dynamic_cast<E*>(entity));
    }

    virtual void fill(const E* entity) {
        if (entity == 0)
            return;
        QString title = "";
        for (int i = 0; i < E::staticMetaObject.propertyCount(); i++) {
            QMetaProperty field = E::staticMetaObject.property(i);
            if (_titleProperties.contains(field.name())) {
                QVariant v = field.read(entity);
                if (v.isValid()) {
                    if (title.isEmpty() == false) {
                        title += " ";
                    }
                    title += v.toString();
                }
            }
        }
        setTitle(new Title(new Text(title)));
        for (int i = 0; i < E::staticMetaObject.propertyCount(); i++) {
            QMetaProperty field = E::staticMetaObject.property(i);
            if (_properties.contains(field.name())) {
                setWidget(field.name(), new Text(field.read(entity).toString()));
            }
        }
    }

    void addPropertyToTitle(const QString& property) {
        if (_titleProperties.contains(property) == false) {
            _titleProperties << property;
        }
    }

    void removePropertyFromTitle(const QString& property) {
        _titleProperties.removeAll(property);
    }

    IWidget* getTitle() const {
        return _title;
    }

    void setTitle(const QString& title) {
        setTitle(new Title(new Text(title)));
    }

    void setTitle(Title* title) {
        if (_title != 0) {
            delete _title;
        }
        _title = title;
    }

    void addProperty(const QString& property) {
        if (_properties.contains(property) == false) {
            _labels[property] = property;
            _properties << property;
            _displayOrder << property;
        }
    }

    void removeProperty(const QString& property) {
        _properties.removeAll(property);
    }

    QStringList getDisplayOrder() const {
        return _displayOrder;
    }

    void setDisplayOrder(const QStringList& order) {
        _displayOrder.clear();
        _displayOrder.append(order);
    }

    QMap<QString, QString> getLabels() const {
        return _labels;
    }

    QString getLabel(const QString& property) {
        return _labels[property];
    }

    void setLabels(const QMap<QString, QString>& labels) {
        _labels = labels;
    }

    void setLabel(const QString& property, const QString& label) {
        _labels[property] = label;
    }

    QMap<QString, IWidget*> getWidgets() const {
        return _propertiesWidgets;
    }

    IWidget* getWidget(const QString& property) const {
        if (_propertiesWidgets.contains(property)) {
            return _propertiesWidgets[property];
        }
        return 0;
    }

    void setWidget(const QString& property, IWidget* widget) {
        if (_propertiesWidgets.contains(property)) {
            delete _propertiesWidgets[property];
        }
        _propertiesWidgets[property] = widget;
    }

    virtual QString render() {
        _widget.clear();
        _content->addWidget(_title);
        Table* details = new Table();
        details->setId("details");
        for (QStringList::iterator it = _displayOrder.begin(); it != _displayOrder.end(); it++) {
            if (_propertiesWidgets.contains(*it)) {
                QList<Container*> row;
                Container* test = new Container();
                test->addWidget(new Text(_labels[*it]));
                row << test;
                Container* propriety = new Container();
                propriety->addWidget(_propertiesWidgets[*it]);
                row << propriety;
                details->addRow(row);
            }
        }
        _content->addWidget(details);
        return _content->render();
    }

};

} // namespace UI

#endif /* MODELENTITYVIEWER_H */
