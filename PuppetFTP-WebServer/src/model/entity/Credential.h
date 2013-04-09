/*
 * Credential.h
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#ifndef CREDENTIAL_H_
#define CREDENTIAL_H_

#include <QObject>
#include <QString>

namespace Model {

class Credential : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32 id           READ getId              WRITE setId             )
    Q_PROPERTY(QString name         READ getName            WRITE setName           )
    Q_PROPERTY(QString description  READ getDescription     WRITE setDescription    )

protected:
    quint32 _id;
    QString _name;
    QString _description;

public:
    Credential();
    Credential(const Credential& credential);
    virtual ~Credential();

    Q_INVOKABLE quint32 getId() const;
    Q_INVOKABLE QString getName() const;
    Q_INVOKABLE QString getDescription() const;

    Q_INVOKABLE void    setId(quint32 id);
    Q_INVOKABLE void    setName(const QString& name);
    Q_INVOKABLE void    setDescription(const QString& description);
};

} // namespace Model

#endif /* CREDENTIAL_H_ */
