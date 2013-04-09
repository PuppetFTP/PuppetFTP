#include "ServerConfList.h"
#include "Server.h"

namespace UI {

ServerConfList::ServerConfList() : ModelEntityList< ::Model::Server >() {
    // Set column
    addColumn("#",       "id"      );
    addColumn("Name",    "name"    );

    // Set order
//    QStringList order;
//    order << "name";
//    setDisplayOrder(order);

    // Set action
    addAction("serverEdit", new Image("/images/icon_edit.png", "Edit"));
}

ServerConfList::~ServerConfList() {
}

} // namespace UI
