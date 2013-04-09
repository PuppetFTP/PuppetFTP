/*
 * RoleModelList.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "RoleModelList.h"
#include "Role.h"
#include "DatabaseManager.h"
#include "ITable.h"


namespace UI {

RoleModelList::RoleModelList() : ModelEntityList< ::Model::Role >() {
    // Set column
    addColumn("#",     "id"   );
    addColumn("Name",  "name" );

    // Set Order
    QStringList order;
    order << "name";
    setDisplayOrder(order);

    // Set Action
    addAction("entityDelete", new Image("/images/icon_delete.png", "Delete"));
    addAction("entityEdit",   new Image("/images/icon_edit.png",   "Edit"));
}

RoleModelList::~RoleModelList() {
}

} // namespace UI
