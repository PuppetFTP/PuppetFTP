/*
 * CorePageRenderer.cpp
 *
 *  Created on: 06 nov. 2012
 *      Author: mtonnelier
 */

#include "PageRenderer.h"
#include "Widget.h"

namespace UI {


PageRenderer::PageRenderer() {
    // Init
    _header = new Container(Container::HEADER);
    _body   = new Container(Container::SECTION);
    _footer = new Container(Container::FOOTER);
}

PageRenderer::~PageRenderer() {
    _stylesheets.clear();
    _javascripts.clear();
    _metatags.clear();
    delete _header;
    delete _body;
    delete _footer;
}

QString                   PageRenderer::getId()                           const { return _id;             }
QString                   PageRenderer::getTitle()                        const { return _title;          }
QMap<QString, QString>    PageRenderer::getMetaTags()                     const { return _metatags;       }
QString                   PageRenderer::getMetaTag(const QString& name)   const { return _metatags[name]; }
QString                   PageRenderer::getFavicon()                      const { return _favicon;        }
QStringList               PageRenderer::getStylesheets()                  const { return _stylesheets;    }
QStringList               PageRenderer::getJavascripts()                  const { return _javascripts;    }

void                      PageRenderer::setId(const QString& id)                                  { _id = id;                    }
void                      PageRenderer::setTitle(const QString& title)                            { _title = title;              }
void                      PageRenderer::setCharset(const QString& charset)                        { _charset = charset;          }
void                      PageRenderer::setFavicon(const QString& favicon)                        { _favicon = favicon;          }
void                      PageRenderer::addMetaTag(const QString& name, const QString& value)     { _metatags[name] = value;     }
void                      PageRenderer::addStylesheet(const QString& url)                         { _stylesheets.push_back(url); }
void                      PageRenderer::addJavascript(const QString& url)                         { _javascripts.push_back(url); }

void                      PageRenderer::clearMetaTags()       { _metatags.clear();     }
void                      PageRenderer::clearStylesheets()    { _stylesheets.clear();  }
void                      PageRenderer::clearJavascripts()    { _javascripts.clear();  }

Container*                PageRenderer::header()              { return _header; }
Container*                PageRenderer::body()                { return _body;   }
Container*                PageRenderer::footer()              { return _footer; }

QString PageRenderer::renderMetaTags() const {
    QString res;
    if (!_charset.isEmpty())
        res.append("<meta charset=\"" + _charset + "\" />\n");
    for (QMap<QString, QString>::const_iterator it = _metatags.begin(); it != _metatags.end(); ++it) {
        res.append("<meta name=\"" + it.key() + "\" content=\"" + it.value() + "\" />\n");
    }
    return res;
}

QString PageRenderer::renderJavascripts() const {
    QString res;
    for (QStringList::const_iterator it = _javascripts.begin(); it != _javascripts.end(); ++it) {
        res.append("<script type=\"text/javascript\" src=\"" + (*it) + "\"></script>\n");
    }
    return res;
}

QString PageRenderer::renderStylesheets() const {
    QString res;
    if (!_favicon.isEmpty())
        res.append("<link href=\"" + _favicon + "\" rel=\"shortcut icon\" type=\"image/x-icon\" />\n");
    for (QStringList::const_iterator it = _stylesheets.begin(); it != _stylesheets.end(); ++it) {
        res.append("<link href=\"" + (*it) + "\" rel=\"stylesheet\" type=\"text/css\" />\n");
    }
    return res;
}

QByteArray PageRenderer::render() const {
    QString res;
    res.append("<!DOCTYPE html>\n");
    res.append("<html>\n");

    // Head
    res.append("  <head>\n");
    res.append("    <title>"+getTitle()+"</title>\n");
    res.append(renderMetaTags());
    res.append(renderStylesheets());
    res.append(renderJavascripts());
    res.append("  </head>\n");

    // Body
    res.append("  <body");
    if (!_id.isEmpty())
        res.append(" id=\""+_id+"\"");
    res.append(">\n");

    if (_header->getWidget().size() > 0)
        res.append(_header->render());
    if (_body->getWidget().size() > 0)
        res.append(_body->render());
    if (_footer->getWidget().size() > 0)
        res.append(_footer->render());

    res.append("  </body>\n");
    res.append("</html>");
    return res.toLatin1();
}

} // namespace UI
