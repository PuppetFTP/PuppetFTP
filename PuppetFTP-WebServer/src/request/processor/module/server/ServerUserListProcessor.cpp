#include "ServerUserListProcessor.h"
#include "DefaultPageRenderer.h"
#include "ModelWidgetFactory.h"
#include "DatabaseManager.h"
#include "Widget.h"
#include "Helper.h"

ServerUserListProcessor::ServerUserListProcessor() : AbstractRequestProcessor() {
}

ServerUserListProcessor::~ServerUserListProcessor() {
}

QStringList ServerUserListProcessor::getRequiredCredentials() const {
    QStringList list;
    return list;
}

void ServerUserListProcessor::process(HTTPRequest& request) {
}

QByteArray ServerUserListProcessor::render() const {
    UI::DefaultPageRenderer page;

    page.setTitle("PuppetFTP - Manage Your Server - User List");

    return page.render();
}
