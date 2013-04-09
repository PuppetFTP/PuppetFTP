/*
 * ServerModelList.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "ServerModelList.h"
#include "Server.h"

namespace UI {

ServerModelList::ServerModelList() : ModelEntityList< ::Model::Server >() {
    // Set column
    addColumn("#",       "id"      );
    addColumn("Name",    "name"    );
    addColumn("Address", "address" );
    addColumn("Port",    "port"    );

    // Set order
//    QStringList order;
//    order << "name" << "address" << "port";
//    setDisplayOrder(order);

    // Set action
    addAction("entityDelete", new Image("/images/icon_delete.png", "Delete"));
    addAction("entityEdit",   new Image("/images/icon_edit.png",   "Edit"));

    // Set button
    addButton("entityAdd", new Text("Add Server"));
}

ServerModelList::~ServerModelList() {
}

} // namespace UI
