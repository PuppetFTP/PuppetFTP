#ifndef MODELWIDGETFACTORY_H
#define MODELWIDGETFACTORY_H

#include "Factory.h"
#include "IModelEntity.h"
#include "IModelList.h"
#include "IModelViewer.h"
#include "IModelEditor.h"
#include <QString>


namespace UI {

class ModelWidgetFactory : Factory<IModelEntity> {
protected:
    static ModelWidgetFactory*                        _instance;

private:
    ModelWidgetFactory();
    virtual ~ModelWidgetFactory();
public:
    static ModelWidgetFactory*  instance();
    static void                 destroy();

    template<typename T>
    static void registerWidget(const QString& name) {
        instance()->registerObject<T>(name);
    }

    IModelEntity* getWidget(const QString &name)       const;
    IModelList*   getListWidget(const QString &name)   const;
    IModelViewer* getViewerWidget(const QString &name) const;
    IModelEditor* getEditorWidget(const QString &name) const;
};

} // namespace UI

#endif // MODELWIDGETFACTORY_H
