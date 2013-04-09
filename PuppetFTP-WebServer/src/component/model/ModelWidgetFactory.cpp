/*
 * ModelWidgetFactory.cpp
 *
 *  Created on: 08 nov. 2012
 *      Author: mtonnelier
 */

#include "ModelWidgetFactory.h"

namespace UI {

ModelWidgetFactory* ModelWidgetFactory::_instance = 0;

ModelWidgetFactory::ModelWidgetFactory() {
}

ModelWidgetFactory::~ModelWidgetFactory(){
}

ModelWidgetFactory* ModelWidgetFactory::instance() {
    if (_instance == 0) {
        _instance = new ModelWidgetFactory();
    }
    return _instance;
}

void ModelWidgetFactory::destroy() {
    if (_instance != 0) {
        delete _instance;
        _instance = 0;
    }
}

IModelEntity* ModelWidgetFactory::getWidget(const QString &name) const {
    return getObject(name);
}

IModelList* ModelWidgetFactory::getListWidget(const QString &name) const {
    return dynamic_cast<IModelList*>(getObject(name));
}

IModelViewer* ModelWidgetFactory::getViewerWidget(const QString &name) const {
    return dynamic_cast<IModelViewer*>(getObject(name));
}

IModelEditor* ModelWidgetFactory::getEditorWidget(const QString& name) const {
    return dynamic_cast<IModelEditor*>(getObject(name));
}

} // namespace UI

