/*
 * ModelEntityFactory.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef MODELENTITYFACTORY_H_
#define MODELENTITYFACTORY_H_

#include <QObject>
#include <QMap>
#include <QString>
#include "Factory.h"
#include "AccessibleServer.h"
#include "Credential.h"
#include "Role.h"
#include "Server.h"
#include "User.h"

namespace Model {

class ModelEntityFactory : private Factory<QObject> {
private:
    static ModelEntityFactory* _instance;

    ModelEntityFactory();
    virtual ~ModelEntityFactory();

public:
    static ModelEntityFactory* instance();
    static void                destroy();

    template<typename T>
    void registerEntity(const QString& name) {
        registerObject<T>(name);
    }
    QObject* getEntity(const QString& name) const;
};

} // namespace Model

#endif /* MODELENTITYFACTORY_H_ */
