#ifndef IMAGE_H
#define IMAGE_H

#include "AbstractWidget.h"
#include "IInlinable.h"

namespace UI {

class Image : public AbstractWidget, public IInlinable {
protected:
    QString     _title;
    QString     _url;
private:
    Image();
public:
    Image(const QString& url);
    Image(const QString& url, const QString& title);
    Image(const Image& obj);
    Image& operator=(const Image& obj);
    virtual ~Image();

    void            setTitle(const QString& title);
    void            setUrl(const QString& url);
    QString         getTitle() const;
    QString         getUrl()   const;
    QString         render()   const;
};

} // namespace UI


#endif // IMAGE_H
