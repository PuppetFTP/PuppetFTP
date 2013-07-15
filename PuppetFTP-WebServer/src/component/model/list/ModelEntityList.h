/*
 * EntityBaseTable.h
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#ifndef MODELENTITYLIST_H
#define MODELENTITYLIST_H

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMap>
#include <QList>
#include <QString>
#include <QVariant>
#include "IModelList.h"
#include "Helper.h"
#include "Widget.h"

namespace UI {

typedef QString (*fnctFormat)(const QVariant&, QMap<QString, QVariant>);

template <typename E>
class ModelEntityList : public IModelList {
protected :
    QList<E*>                            _objects;
    Container*                           _content;
    QStringList                          _displayOrder;
    QHash<QString, Link*>          _actions;
    QMap<QString, IInlinable*>           _buttons;
    QMap<QString, QString>               _cols;
    QMap<QString, fnctFormat>            _format;

public:
    ModelEntityList() {
        _content = new Container(Container::SECTION);
    }

    virtual ~ModelEntityList() {
        delete _content;
    }

    virtual void fill(const QList<QObject*>& objects) {
        QList<E*> l;
        for (QList<QObject*>::const_iterator it = objects.begin(); it != objects.end(); it++) {
            E* o = dynamic_cast<E*>(*it);
            if (o != 0) {
                l << o;
            }
        }
        fill(l);
    }

    virtual void fill(const QList<E*>& objects) {
        QMap<QString, QVariant> params;
        // Param url
        QString classname(E::staticMetaObject.className());
        QStringList tmp = classname.split("::");
        if (tmp.size() > 1) {
            params["entity"] = tmp.at(tmp.size() - 1);
        } else {
            params["entity"] = classname;
        }
        // Set Button
        _content->addWidget(setButton(params));

        Table* table = new Table();
        table->addClass("table table-hover");
        _objects.clear();
        _objects.append(objects);

        // Header
        QString col;
        foreach (col, _displayOrder) {
            Container* head = new Container(Container::NONE);
            head->addWidget(new Text(_cols[col]));
            table->addHeader(head);
        }
        Container* head = new Container(Container::NONE);
        head->addWidget(new Text("Action"));
        table->addHeader(head);

        // Body
        QMap<QString, int> propertyToIndex;
        for (int i = 0; i < E::staticMetaObject.propertyCount(); i++) {
            if (_cols.keys().contains(E::staticMetaObject.property(i).name())) {
                propertyToIndex[E::staticMetaObject.property(i).name()] = i;
            }
        }

        for (typename QList<E*>::iterator it0 = _objects.begin(); it0 != _objects.end(); it0++) {
            QList<Container*> row;
            foreach (col, _displayOrder) {
                QMetaProperty field = E::staticMetaObject.property(propertyToIndex[col]);
                QVariant v = field.read(*it0);
                if (QString(field.name()) == "id") {
                    params["id"] = v;
                }
                Container* head = new Container(Container::NONE);
                if (_format.contains(field.name())) {
                    v = _format[field.name()](v, params);
                }
                head->addWidget(new Text(v.toString()));
                row << head;
            }
            row << setAction(params);
            table->addRow(row);
        }
        _content->addWidget(table);
    }

    void addColumn(const QString& name, const QString& property) {
        _cols[property] = name;
        if (_displayOrder.contains(property))
            _displayOrder.removeAll(property);
        _displayOrder << property;
    }

    QStringList getDisplayOrder() const {
        return _displayOrder;
    }

    void setDisplayOrder(const QStringList& order) {
        _displayOrder.clear();
        _displayOrder.append(order);
    }

    Container* getContent() const {
        return _content;
    }

    void setFormat(const QString& property, const fnctFormat& fnct) {
        _format[property] = fnct;
    }

    void addAction(QString url, Link* inlinable) {
        _actions[url] = inlinable;
    }

    Container* setAction(QMap<QString, QVariant> params) {
        Container* actions = new Container();
        actions->addClass("action");
        for (QHash<QString, Link*>::const_iterator it = _actions.begin(); it != _actions.end(); it++) {
            Link* link = new Link(*it.value());
            link->setUrl(Helper::gen_url(it.key(), params));
            actions->addWidget(link);
        }
        return actions;
    }

    void addButton(QString url, IInlinable* inlinable) {
        _buttons[url] = inlinable;
    }

    Container* setButton(QMap<QString, QVariant> params) {
        Container* buttons = new Container(Container::NONE);
        for (QMap<QString, IInlinable*>::const_iterator it = _buttons.begin(); it != _buttons.end(); it++) {
            IWidget* link = new Link(Helper::gen_url(it.key(), params), it.value());
            link->addClass("btn");
            link->setAttribute("rel", "shadowbox; width=500;height=390");
            buttons->addWidget(link);
        }
        return buttons;
    }
};

} // namespace UI

#endif // MODELENTITYLIST_H
