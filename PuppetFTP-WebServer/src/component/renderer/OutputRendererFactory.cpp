/*
 * OutputRendererFactory.cpp
 *
 *  Created on: 08 nov. 2012
 *      Author: mtonnelier
 */

#include "OutputRendererFactory.h"

namespace UI {

OutputRendererFactory* OutputRendererFactory::_instance = 0;

OutputRendererFactory::OutputRendererFactory() {
}

OutputRendererFactory::~OutputRendererFactory(){
}

OutputRendererFactory* OutputRendererFactory::instance() {
    if (_instance == 0) {
        _instance = new OutputRendererFactory();
    }
    return _instance;
}

void OutputRendererFactory::destroy() {
    if (_instance != 0) {
        delete _instance;
        _instance = 0;
    }
}

IOutputRenderer* OutputRendererFactory::getRenderer(const QString &name) const {
    return getObject(name);
}

} // namespace UI
