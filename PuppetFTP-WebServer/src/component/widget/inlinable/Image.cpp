#include "Image.h"

namespace UI {

Image::Image() {
}

Image::Image(const QString& url) {
    setAttribute("src", url);
}

Image::Image(const QString& url, const QString& title) {
    setAttribute("src", url);
    setAttribute("alt", title);
    setAttribute("title", title);
}

Image::Image(const Image& obj) {
    _attributes = obj.getAttributes();
}

Image& Image::operator=(const Image& obj) {
    _attributes = obj.getAttributes();
    return *this;
}

Image::~Image() {
}

void            Image::setTitle(const QString& title)   { setAttribute("alt", title); }
void            Image::setUrl(const QString& url)       { setAttribute("src", url);   }
QString         Image::getTitle()                 const { return getAttribute("alt"); }
QString         Image::getUrl()                   const { return getAttribute("src"); }

QString         Image::render()                   const {
    QString res;

    res.append("<img" + renderAttribute() + " />");
    return res;
}

} // namespace UI
