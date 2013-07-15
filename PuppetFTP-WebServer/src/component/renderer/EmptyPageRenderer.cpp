/*
 * EmptyPageRenderer.cpp
 *
 *  Created on: 17 juin 2012
 *      Author: mtonnelier
 */

#include <QDate>
#include "EmptyPageRenderer.h"

namespace UI {

EmptyPageRenderer::EmptyPageRenderer() {
    // Head
    addMetaTag("keywords", "puppet, puppetFTP, FTP, proFTPd, vsFTPd");
    addMetaTag("description", "Administration de serveur FTP");
    addMetaTag("robots", "index,follow");
    setFavicon("/img/favicon.ico");
    addStylesheet("/css/bootstrap-min.css");
    addStylesheet("/css/shadowbox.css");
    addStylesheet("http://fonts.googleapis.com/css?family=Muli:300");
    addStylesheet("/css/style-sbx.css");
    addJavascript("/js/jquery-min.js");
    addJavascript("/js/shadowbox.js");
}

EmptyPageRenderer::~EmptyPageRenderer() {
}

} // namespace UI
