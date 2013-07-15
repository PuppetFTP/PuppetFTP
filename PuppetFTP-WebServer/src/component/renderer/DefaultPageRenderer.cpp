/*
 * DefaultPageRenderer.cpp
 *
 *  Created on: 06 nov. 2012
 *      Author: mtonnelier
 */

#include <QDate>
#include "DefaultPageRenderer.h"
#include "Widget.h"
#include "Helper.h"
#include "Translate.h"

namespace UI {

DefaultPageRenderer::DefaultPageRenderer(const bool disabled) :
    _disabledMenu(disabled) {
    // Head
    addMetaTag("keywords", "puppet, puppetFTP, FTP, proFTPd, vsFTPd");
    addMetaTag("description", "Administration de serveur FTP");
    addMetaTag("robots", "index,follow");
    setFavicon("/img/favicon.ico");
    addStylesheet("/css/bootstrap.min.css");
    addStylesheet("/css/style.css");
    addStylesheet("/css/shadowbox.css");
    addStylesheet("http://fonts.googleapis.com/css?family=Muli:300");
    addStylesheet("/css/jquery.ambiance.css");
    addJavascript("/js/jquery.min.js");
    addJavascript("/js/jquery.ambiance.js");
    addJavascript("/js/shadowbox.js");
    addJavascript("/js/puppetftp.js");

    // Header
    // Logo
    Image* img = new Image("/img/logo.png", "puppetFTP.com");
    img->setId("logo_img");
    img->setAttribute("width", "350");

    Link* link = new Link(Helper::gen_url("index"), img);
    Container* logo = new Container();
    logo->setId("logo");
    logo->addWidget(link);
    header()->addWidget(logo);

    Translate::instance()->group("default");
    if (_disabledMenu == false) {
        // Menu
        Container* menu = new Container(Container::NAV);
        {
            Container* imgHome = new Container();
            imgHome->addWidget(new Image("/img/icon_home.png", Translate::instance()->tr("button_home")));
            menu->addWidget(imgHome);

            Container* linkHome = new Container();
            linkHome->addClass("link");
            linkHome->addWidget(new Link(Helper::gen_url("index"), new Text(Translate::instance()->tr("button_home"))));
            menu->addWidget(linkHome);

            Container* imgLogout = new Container();
            imgLogout->addWidget(new Image("/img/icon_logout.png", Translate::instance()->tr("button_logout")));
            menu->addWidget(imgLogout);

            Container* linkLogout = new Container();
            linkLogout->addClass("link");
            linkLogout->addWidget(new Link(Helper::gen_url("logout"), new Text(Translate::instance()->tr("button_logout"))));
            menu->addWidget(linkLogout);
        }
        header()->addWidget(menu);

        Container* hidden = new Container();
        hidden->setAttribute("style", "clear:both;visibility:hidden;");
        hidden->addWidget(new Text("&nbsp;"));
        header()->addWidget(hidden);
    }

    // Footer
    Container* foot = new Container(Container::PARAGRAPH);
    QDate date      = QDate::currentDate();
    foot->addWidget(new Text("PuppetFTP © 2012/" + date.toString("yyyy") + " - "));
    foot->addWidget(new Text(Translate::instance()->tr("copyright")));
    if (_disabledMenu == false) {
        QMap<QString, QVariant> param;
        param["entity"] = "user";
        foot->addWidget(new Text(" - "));
        foot->addWidget(new Link(Helper::gen_url("entityList", param), new Text(Translate::instance()->tr("manage"))));
    }
    footer()->addWidget(foot);
}

DefaultPageRenderer::~DefaultPageRenderer() {
}

} // namespace UI
