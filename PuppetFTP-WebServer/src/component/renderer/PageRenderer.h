/*
 * CorePageRenderer.h
 *
 *  Created on: 06 nov. 2012
 *      Author: mtonnelier
 */

#ifndef COREPAGERENDERER_H
#define COREPAGERENDERER_H

#include "IOutputRenderer.h"
#include "IWidget.h"
#include "Container.h"
#include <QMap>
#include <QString>
#include <QStringList>

namespace UI {

/**
 * Class Definition
 */
class PageRenderer: public IOutputRenderer {
private:
    QString                   _title;
    QString                   _id;
    QMap<QString, QString>    _metatags;
    QString                   _favicon;
    QString                   _charset;
    QStringList               _stylesheets;
    QStringList               _javascripts;

    Container*                _header;
    Container*                _body;
    Container*                _footer;

public:
    PageRenderer();
    ~PageRenderer();

    QString                   getId()                           const;
    QString                   getTitle()                        const;
    QMap<QString, QString>    getMetaTags()                     const;
    QString                   getMetaTag(const QString& name)   const;
    QString                   getFavicon()                      const;
    QStringList               getStylesheets()                  const;
    QStringList               getJavascripts()                  const;


    void                      setId(const QString& id);
    void                      setTitle(const QString& title);
    void                      setCharset(const QString& charset);
    void                      setFavicon(const QString& favicon);
    void                      addMetaTag(const QString& name, const QString& value);
    void                      addStylesheet(const QString& url);
    void                      addJavascript(const QString& url);

    void                      clearMetaTags();
    void                      clearStylesheets();
    void                      clearJavascripts();

    Container*                header();
    Container*                body();
    Container*                footer();

    virtual                   QByteArray render() const;

protected:
    QString                   renderMetaTags() const;
    QString                   renderStylesheets() const;
    QString                   renderJavascripts() const;
};

} // namespace UI

#endif // COREPAGERENDERER_H
