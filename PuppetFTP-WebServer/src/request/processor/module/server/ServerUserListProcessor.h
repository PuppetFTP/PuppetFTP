#ifndef SERVERUSERLISTPROCESSOR_H
#define SERVERUSERLISTPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"
#include "IModelList.h"

class ServerUserListProcessor: public AbstractRequestProcessor {
protected:
    QString         _type;
    QString         _entityName;
    UI::IModelList* _table;

public:
    ServerUserListProcessor();
    virtual ~ServerUserListProcessor();

    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // SERVERUSERLISTPROCESSOR_H
