#include "Image.h"

namespace UI {

Image::Image() {
    _url   = "";
    _title = "";
}

Image::Image(const QString& url) {
    _url   = url;
    _title = "";
}

Image::Image(const QString& url, const QString& title) {
    _url   = url;
    _title = title;
}

Image::Image(const Image& obj) {
    _title      = obj.getTitle();
    _url        = obj.getUrl();
    _attributes = obj.getAttributes();
}

Image& Image::operator=(const Image& obj) {
    _title      = obj.getTitle();
    _url        = obj.getUrl();
    _attributes = obj.getAttributes();
    return *this;
}

Image::~Image() {
}

void            Image::setTitle(const QString& title)   { _title = title; }
void            Image::setUrl(const QString& url)       { _url = url;     }
QString         Image::getTitle()                 const { return _title;  }
QString         Image::getUrl()                   const { return _url;    }

QString         Image::render()                   const {
    QString res;

    res.append("<img" + renderAttribute() + " src=\"");
    res.append(_url);
    if (!_title.isEmpty()) {
        res.append("\" alt=\"");
        res.append(_title);
    }
    res.append("\"/>");
    return res;
}

} // namespace UI
