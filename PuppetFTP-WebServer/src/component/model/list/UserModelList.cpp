/*
 * UserModelList.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#include "UserModelList.h"
#include "User.h"
#include "Helper.h"

namespace UI {

UserModelList::UserModelList() : ModelEntityList< ::Model::User >() {
    // Set Column
    addColumn("#",           "id"           );
    addColumn("Last name",   "lastname"     );
    addColumn("First name",  "firstname"    );
//    addColumn("Mail",        "email"        );
    addColumn("Last access", "last_access"  );

    // Set order
//    QStringList order;
//    order << "lastname" << "firstname" << "email" << "last_access";
//    setDisplayOrder(order);

    // Set action
    addAction("entityDelete", new Image("/images/icon_delete.png", "Delete"));
    addAction("entityEdit",   new Image("/images/icon_edit.png",   "Edit"));

    // Set button
    addButton("entityAdd", new Text("Add User"));

    // Set format column
    setFormat("last_access", &Helper::formatQdateTime);
}

UserModelList::~UserModelList() {
}

} // namespace UI
