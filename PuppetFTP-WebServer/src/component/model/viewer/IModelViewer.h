/*
 * IModelViewer.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef IMODELVIEWER_H_
#define IMODELVIEWER_H_

#include <QObject>
#include "IWidget.h"
#include "IModelEntity.h"

namespace UI {

/**
 * Only used for type specialization
 */
class IModelViewer : public IModelEntity {
public:
    virtual ~IModelViewer() {}
    virtual void fill(QObject* entity) = 0;
};

} // namespace UI

#endif /* IMODELVIEWER_H_ */
