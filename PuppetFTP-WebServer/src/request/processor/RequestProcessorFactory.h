/*
 * RequestProcessorFactory.h
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#ifndef REQUESTPROCESSORFACTORY_H_
#define REQUESTPROCESSORFACTORY_H_

#include <QString>
#include "Factory.h"
#include "IRequestProcessor.h"

class RequestProcessorFactory : private Factory<IRequestProcessor> {
private:
    static RequestProcessorFactory* _instance ;

    RequestProcessorFactory();
    ~RequestProcessorFactory();

public:
    static RequestProcessorFactory* instance();
    static void                     destroy();

    IRequestProcessor*              getProcessor(const QString& name) const;

    template<typename T>
    void                            registerProcessor(const QString& name) {
        registerObject<T>(name);
    }
//    void                            registerRequestProcessor(IRequestProcessor* processor);
};

#endif // REQUESTPROCESSORFACTORY_H_
