/*
 * AccessibleServerModelList.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "AccessibleServerModelList.h"
#include "AccessibleServer.h"
#include "DatabaseManager.h"
#include "ITable.h"

namespace UI {

AccessibleServerModelList::AccessibleServerModelList() : ModelEntityList< ::Model::AccessibleServer >() {
    // Set column
    addColumn("User",   "user"   );
    addColumn("Server", "server" );
    addColumn("Role",   "role"   );

    // Set action
    addAction("entityDelete", new Image("/images/icon_delete.png", "Delete"));
    addAction("entityEdit",   new Image("/images/icon_edit.png",   "Edit"));
}

AccessibleServerModelList::~AccessibleServerModelList() {
}

} // namespace UI
