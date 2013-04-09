/*
 * CredentialModelList.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "CredentialModelList.h"
#include "Credential.h"
#include "DatabaseManager.h"
#include "ITable.h"

namespace UI {

CredentialModelList::CredentialModelList() : ModelEntityList< ::Model::Credential >() {
    // Set Column
    addColumn("#",     "id"   );
    addColumn("Name",  "name" );

    // Set order
    QStringList order;
    order << "name";
    setDisplayOrder(order);

    // Set action
    addAction("entityDelete", new Image("/images/icon_delete.png", "Delete"));
    addAction("entityEdit",   new Image("/images/icon_edit.png",   "Edit"));
}

CredentialModelList::~CredentialModelList() {
}

} // namespace UI
