/*
 * OutputRendererFactory.h
 *
 *  Created on: 08 nov. 2012
 *      Author: mtonnelier
 */

#ifndef OUTPUTRENDERERFACTORY_H
#define OUTPUTRENDERERFACTORY_H

#include "Factory.h"
#include "IOutputRenderer.h"
#include <QString>

namespace UI {

class OutputRendererFactory : Factory<IOutputRenderer> {
protected:
    static OutputRendererFactory*           _instance;

private:
    OutputRendererFactory();
    virtual ~OutputRendererFactory();
public:
    static OutputRendererFactory*  instance();
    static void                    destroy();

    template<typename T>
    static void registerRenderer(const QString& name) {
        instance()->registerObject<T>(name);
    }

    IOutputRenderer* getRenderer(const QString &name) const;
};

} // namespace UI


#endif // OUTPUTRENDERERFACTORY_H
