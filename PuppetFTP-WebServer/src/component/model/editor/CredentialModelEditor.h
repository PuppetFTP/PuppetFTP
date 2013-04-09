/*
 * CredentialForm.h
 *
 *  Created on: 14 nov. 2012
 *      Author: laplace
 */

#ifndef CREDENTIALMODELEDITOR_H
#define CREDENTIALMODELEDITOR_H

#include "ModelEntityEditor.h"
#include "Credential.h"

namespace UI {

class CredentialModelEditor : public ModelEntityEditor< ::Model::Credential > {
public:
    CredentialModelEditor();
    virtual ~CredentialModelEditor();
};

} // namespace UI

#endif /* CREDENTIALMODELEDITOR_H */
