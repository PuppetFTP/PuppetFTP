#ifndef SERVERCONFLIST_H
#define SERVERCONFLIST_H

#include "ModelEntityList.h"
#include "Server.h"
#include "IWidget.h"

namespace UI {

class ServerConfList : public ModelEntityList< ::Model::Server > {
public:
    ServerConfList();
    virtual ~ServerConfList();
};

} // namespace UI

#endif // SERVERCONFLIST_H
