/*
 * UserModelViewer.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef USERMODELVIEWER_H
#define USERMODELVIEWER_H

#include "ModelEntityViewer.h"
#include "User.h"


namespace UI {

class UserModelViewer: public ModelEntityViewer< ::Model::User > {
public:
    UserModelViewer();
    virtual ~UserModelViewer();
};

} // namespace UI

#endif /* USERMODELVIEWER_H */
