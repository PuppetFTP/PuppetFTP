/*
 * UserModelList.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef USERMODELLIST_H_
#define USERMODELLIST_H_

#include "ModelEntityList.h"
#include "IWidget.h"
#include "User.h"

namespace UI {

class UserModelList: public ModelEntityList< ::Model::User > {
public:
    UserModelList();
    virtual ~UserModelList();
};

} // namespace UI


#endif /* USERMODELLIST_H_ */
