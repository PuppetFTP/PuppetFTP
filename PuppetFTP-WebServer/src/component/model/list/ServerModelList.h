/*
 * ServerModelList.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef SERVERMODELLIST_H
#define SERVERMODELLIST_H

#include "ModelEntityList.h"
#include "Server.h"
#include "IWidget.h"

namespace UI {

class ServerModelList : public ModelEntityList< ::Model::Server > {
public:
    ServerModelList();
    virtual ~ServerModelList();
};

} // namespace UI

#endif /* SERVERMODELLIST_H */
