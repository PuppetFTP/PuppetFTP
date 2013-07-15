/*
 * UserModelList.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#include "UserModelList.h"
#include "User.h"
#include "Helper.h"
#include "Translate.h"

namespace UI {

UserModelList::UserModelList() : ModelEntityList< ::Model::User >() {
    Translate::instance()->group("listing_user");
    // Set Column
    addColumn(Translate::instance()->tr("id"),        "id"           );
    addColumn(Translate::instance()->tr("lastname"),  "lastname"     );
    addColumn(Translate::instance()->tr("firstname"), "firstname"    );
//    addColumn(Translate::instance()->tr("mail"),      "email"        );
    addColumn(Translate::instance()->tr("access"),    "last_access"  );

    // Set order
//    QStringList order;
//    order << "lastname" << "firstname" << "email" << "last_access";
//    setDisplayOrder(order);

    Translate::instance()->group("listing");
    // Set action
    Text* edit = new Text("");
    edit->addClass("icon-edit");
    edit->setAttribute("title", Translate::instance()->tr("action_edit"));
    Link* linkEdit = new Link("#", edit);
    linkEdit->setAttribute("rel", "shadowbox; width=500;height=390");
    addAction("entityEdit",   linkEdit);

    Text* del = new Text("");
    del->addClass("icon-trash");
    del->setAttribute("title", Translate::instance()->tr("action_delete"));
    Link* linkDel = new Link("#", del);
    linkDel->setAttribute("rel", "shadowbox; width=500;height=110");
    addAction("entityDelete", linkDel);

    Translate::instance()->group("listing_user");
    // Set button
    addButton("entityAdd", new Text(Translate::instance()->tr("button_add")));

    // Set format column
    setFormat("last_access", &Helper::formatQdateTime);
}

UserModelList::~UserModelList() {
}

} // namespace UI
