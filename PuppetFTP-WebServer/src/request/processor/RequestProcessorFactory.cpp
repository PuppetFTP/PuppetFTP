/*
 * RequestProcessorFactory.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: laplace
 */

#include "RequestProcessorFactory.h"

RequestProcessorFactory* RequestProcessorFactory::_instance = 0;

RequestProcessorFactory::RequestProcessorFactory() {
}

RequestProcessorFactory::~RequestProcessorFactory() {
}

RequestProcessorFactory* RequestProcessorFactory::instance() {
    if (_instance == 0) {
        _instance = new RequestProcessorFactory();
    }
    return _instance;
}

void RequestProcessorFactory::destroy() {
    if (_instance != 0) {
        delete _instance;
    }
}

IRequestProcessor* RequestProcessorFactory::getProcessor(const QString& name) const {
    return getObject(name);
}

//void RequestProcessorFactory::registerRequestProcessor(IRequestProcessor* processor) {
//    if (_processors.contains(processor->getName()) && _processors[processor->getName()] != 0) {
//        qWarning() << "A request processor named" << processor->getName() << "already registered, override it";
//        delete _processors[processor->getName()];
//    }
//    _processors[processor->getName()] = processor;
//}
