/*
 * UserModelEditor.h
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#ifndef USERMODELEDITOR_H
#define USERMODELEDITOR_H

#include "ModelEntityEditor.h"
#include "User.h"


namespace UI {

class UserModelEditor : public ModelEntityEditor< ::Model::User > {
public:
    UserModelEditor();
    virtual ~UserModelEditor();

private:
    void initCustomField();
};

} // namespace UI

#endif /* USERMODELEDITOR_H */
