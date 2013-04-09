/*
 * Factory.h
 *
 *  Created on: 27 nov. 2012
 *      Author: laplace
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include <QHash>
#include <QString>


template<typename Base, typename T> Base* createT() { return new T; }

template<typename Base>
class Factory {
private:
    QHash<QString, Base*(*)()>  _objects;

public:
    Factory() {}
    virtual ~Factory() {}

    template<typename T> void registerObject(const QString& name) {
        _objects[name] = &createT<Base, T>;
    }

    Base* getObject(const QString& name) const {
        if (_objects.contains(name) == false)
            return 0;
        return _objects.value(name)();
    }
};

#endif /* FACTORY_H_ */

