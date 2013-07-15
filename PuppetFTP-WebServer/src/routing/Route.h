/*
 * Route.h
 *
 *  Created on: 23 oct. 2012
 *      Author: laplace
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include <QDebug>
#include <QString>
#include <QMap>
#include <QHash>
#include <QStringList>

namespace Routing {

class Route {
private:
    QString                _name;
    QString                _uri;
    QString                _module;
    QString                _processor;
    QMap<QString, QString> _requirements;
    QStringList            _defaultRequiredCredentials;
    QHash<QPair<QString, QString>, QStringList> _requiredCredentials;

    Route();

public:
    Route(const QString& name);
    virtual ~Route();

    QString                getName()                                                                        const;
    QString                getUri()                                                                         const;
    QString                getProcessor()                                                                   const;
    QString                getModule()                                                                      const;
    QString                getRequirement(const QString& name)                                              const;
    QMap<QString, QString> getRequirements()                                                                const;
    QStringList              getDefaultRequiredCredentials()                                                  const;
    QHash<QPair<QString, QString>, QStringList> getRequiredCredentials()                                                         const;

    void                   setName(const QString& name);
    void                   setUri(const QString& uri);
    void                   setProcessor(const QString& processor);
    void                   setModule(const QString& module);
    void                   setRequirement(const QString& name, const QString value);
    void                   setRequirements(const QMap<QString, QString>& requirements);
    void                   setDefaultRequiredCredential(const QString& credential);
    void                   setRequiredCredential(const QPair<QString, QString>& parameter, const QString& credential);

    QString                toString() const;
};

} // namespace Routing

QDebug       operator<<(QDebug debug, const Routing::Route& route);
QDebug       operator<<(QDebug debug, Routing::Route* route);

#endif /* ROUTE_H_ */
