/*
 * UserModelEditor.h
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#ifndef SERVERMODELEDITOR_H
#define SERVERMODELEDITOR_H

#include "ModelEntityEditor.h"
#include "Server.h"


namespace UI {

class ServerModelEditor : public ModelEntityEditor< ::Model::Server > {
public:
   ServerModelEditor();
   virtual ~ServerModelEditor();
};

} // namespace UI

#endif /* SERVERMODELEDITOR_H */
