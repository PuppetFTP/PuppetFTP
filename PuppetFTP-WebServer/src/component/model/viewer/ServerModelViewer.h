/*
 * ServerModelViewer.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef SERVERMODELVIEWER_H
#define SERVERMODELVIEWER_H

#include "ModelEntityViewer.h"
#include "Server.h"


namespace UI {

class ServerModelViewer: public ModelEntityViewer< ::Model::Server > {
public:
    ServerModelViewer();
    virtual ~ServerModelViewer();
};

} // namespace UI

#endif /* SERVERMODELVIEWER_H */
