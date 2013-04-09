/*
 * ImportexportProcessor.cpp
 *
 *  Created on: 11 nov. 2012
 *      Author: mtonnelier
 */

#include "ImportexportProcessor.h"
#include "SessionManager.h"
#include "Session.h"

#include "DefaultPageRenderer.h"
#include "OutputRendererFactory.h"
#include "Helper.h"
#include "Widget.h"

ImportexportProcessor::ImportexportProcessor(const QString& name) : AbstractRequestProcessor(name) {
}

ImportexportProcessor::~ImportexportProcessor() {
}

QStringList ImportexportProcessor::getRequiredCrendentials() const {
    QStringList list;
    return list;
}

void ImportexportProcessor::process(HTTPRequest& request) {
    _type = request.getParameter("type").toString();
}

QByteArray ImportexportProcessor::render() const {
    Renderer::DefaultPageRenderer* page = Renderer::OutputRendererFactory::getInstance()->getRenderer<Renderer::DefaultPageRenderer>("default");
    if (page == 0) {
      // TBD: gestion d'erreur non définis, soit on set un flag sur le request,
      // soit on lance une exception, a voir, j'me suis pas encore décidé
    }
    page->setTitle("PuppetFTP - Imprort/Export");
    page->setId("users");
    page->setType(_type);
    page->setSubTitle("Import/Export");

    return page->render();
}

