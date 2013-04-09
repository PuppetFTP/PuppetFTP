/*
 * ImportexportProcessor.h
 *
 *  Created on: 11 nov. 2012
 *      Author: mtonnelier
 */

#ifndef IMPORTEXPORTPROCESSOR_H
#define IMPORTEXPORTPROCESSOR_H

#include <QString>
#include <QByteArray>
#include "AbstractRequestProcessor.h"

class ImportexportProcessor: public AbstractRequestProcessor {
protected:
    QString _type;
private:
    ImportexportProcessor();
public:
    ImportexportProcessor(const QString& name);
    virtual ~ImportexportProcessor();

    QStringList getRequiredCrendentials() const;
    void        process(HTTPRequest& request);
    QByteArray  render() const;
};

#endif // IMPORTEXPORTPROCESSOR_H
