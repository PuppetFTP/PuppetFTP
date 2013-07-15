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
#include "Translate.h"

namespace UI {

CredentialModelList::CredentialModelList() : ModelEntityList< ::Model::Credential >() {
    Translate::instance()->group("listing_credential");
    // Set Column
    addColumn(Translate::instance()->tr("id"),    "id"   );
    addColumn(Translate::instance()->tr("name"),  "name" );

    // Set order
    QStringList order;
    order << "name";
    setDisplayOrder(order);

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
}

CredentialModelList::~CredentialModelList() {
}

} // namespace UI
