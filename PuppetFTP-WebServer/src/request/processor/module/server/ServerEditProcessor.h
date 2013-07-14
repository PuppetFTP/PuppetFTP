#ifndef SERVEREDITPROCESSOR_H
# define SERVEREDITPROCESSOR_H

#include "AbstractRequestProcessor.h"
#include "IModelEditor.h"

class ServerEditProcessor: public AbstractRequestProcessor {
protected:
    int               _id;
    UI::IModelEditor* _form;
public:
    ServerEditProcessor();
    virtual ~ServerEditProcessor();

    QStringList getRequiredCredentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // SERVEREDITPROCESSOR_H
