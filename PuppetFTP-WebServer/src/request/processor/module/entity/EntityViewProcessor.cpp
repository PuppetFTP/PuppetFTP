/*
 * EntityViewProcessor.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: mtonnelier
 */

#include "EntityViewProcessor.h"
#include "SessionManager.h"
#include "Session.h"

#include "DefaultPageRenderer.h"
#include "OutputRendererFactory.h"
#include "Helper.h"
#include "Widget.h"

EntityViewProcessor::EntityViewProcessor() : AbstractRequestProcessor() {
}

EntityViewProcessor::~EntityViewProcessor() {
}

QStringList EntityViewProcessor::getRequiredCrendentials() const {
    QStringList list;
    return list;
}

void EntityViewProcessor::process(HTTPRequest& request) {
    _type = request.getParameter("type").toString();
}

QByteArray EntityViewProcessor::render() const {
    UI::DefaultPageRenderer page;

    page.setTitle("PuppetFTP - Configure");
    return page.render();
}

