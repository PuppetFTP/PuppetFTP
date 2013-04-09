/*
 * CredentialViewer.h
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#ifndef CREDENTIALMODELVIEWER_H
#define CREDENTIALMODELVIEWER_H

#include "ModelEntityViewer.h"
#include "Credential.h"


namespace UI {

class CredentialModelViewer: public ModelEntityViewer< ::Model::Credential > {
public:
    CredentialModelViewer();
    virtual ~CredentialModelViewer();
};

} // namespace UI

#endif /* CREDENTIALMODELVIEWER_H */
