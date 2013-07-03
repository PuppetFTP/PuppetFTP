#include "ServerConfList.h"
#include "Server.h"
#include "Translate.h"

namespace UI {

ServerConfList::ServerConfList() : ModelEntityList< ::Model::Server >() {

    Translate::instance()->group("listing_server");
    // Set column
    addColumn(Translate::instance()->tr("id"),      "id"      );
    addColumn(Translate::instance()->tr("name"),    "name"    );
    addColumn(Translate::instance()->tr("address"), "address" );
    addColumn(Translate::instance()->tr("port"),    "port"    );

    Translate::instance()->group("listing");
    // Set action

    Text* server = new Text("");
    server->addClass("icon-wrench");
    server->setAttribute("title", Translate::instance()->tr("action_manage"));
    Link* linkServer = new Link("#", server);
    addAction("serverManage", linkServer);

    Text* edit = new Text("");
    edit->addClass("icon-edit");
    edit->setAttribute("title", Translate::instance()->tr("action_edit"));
    Link* linkEdit = new Link("#", edit);
    linkEdit->setAttribute("rel", "shadowbox; width=500;height=390");
    addAction("entityEdit", linkEdit);

    Text* del = new Text("");
    del->addClass("icon-trash");
    del->setAttribute("title", Translate::instance()->tr("action_delete"));
    Link* linkDel = new Link("#", del);
    linkDel->setAttribute("rel", "shadowbox; width=500;height=110");
    addAction("entityDelete", linkDel);

    Translate::instance()->group("listing_server");
    // Set button
    addButton("entityAdd", new Text(Translate::instance()->tr("button_add")));

    // Set format column
    setFormat("name", &formatSetServerEditLink);
}

ServerConfList::~ServerConfList() {
}

QString formatSetServerEditLink(const QVariant& value, QMap<QString, QVariant> params)
{
    Link* link = new Link(Helper::gen_url("serverManage", params), new Text(value.toString()));
    return link->render();
}

} // namespace UI
