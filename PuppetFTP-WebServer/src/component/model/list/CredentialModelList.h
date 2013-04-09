/*
 * CredentialModelList.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef CREDENTIALMODELLIST_H
#define CREDENTIALMODELLIST_H

#include "ModelEntityList.h"
#include "Credential.h"
#include "IWidget.h"


namespace UI {

class CredentialModelList : public ModelEntityList< ::Model::Credential > {
public:
    CredentialModelList();
    virtual ~CredentialModelList();
};

} // namespace UI

#endif /* CREDENTIALMODELLIST_H */
