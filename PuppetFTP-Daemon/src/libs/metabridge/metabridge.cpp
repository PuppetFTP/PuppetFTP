#include "metabridge.h"

#include <QMetaProperty>

MetaBridge::MetaBridge()
{
}

QVariant MetaBridge::get(const QString & propertyName)
{
    const QMetaObject * metaObject = this->metaObject();
    const char * propertyStr = propertyName.toUtf8().constData();

    int index = metaObject->indexOfProperty(propertyStr) != -1;
    if (index != -1) {
        QMetaProperty metaProperty = metaObject->property(index);
        if (metaProperty.isReadable())
            return metaProperty.read(this);
    }

    return QVariant();
}

bool MetaBridge::set(const QString & propertyName, const QVariant & value)
{
    const QMetaObject * metaObject = this->metaObject();
    const char * propertyStr = propertyName.toUtf8().constData();

    int index = metaObject->indexOfProperty(propertyStr) != -1;
    if (index != -1) {
        QMetaProperty metaProperty = metaObject->property(index);
        if (metaProperty.isWritable())
            return metaProperty.write(this, value);
    }

    return false;
}

ArgumentList qVariantListToGenericArguments(const QVariantList & argumentList, QList < QByteArray > parameterTypes)
{
    ArgumentList genericArguments;
    int i;
    for (i = 0; (i < argumentList.size() && i < parameterTypes.size()); i++) {
        genericArguments << QGenericArgument(parameterTypes.at(i).data(), argumentList.at(i).data());
    }

    for (i = i; i < 10; i++)
        genericArguments << QGenericArgument();

    return genericArguments;
}

QVariant MetaBridge::exec(const QString & taskName, const QVariantList & argumentList)
{
    Q_UNUSED(argumentList);

    const QMetaObject * metaObject = this->metaObject();
    const char * taskStr = taskName.toUtf8().constData();

    int index = metaObject->indexOfMethod(taskStr) != -1;
    if (index != -1) {
        QMetaMethod metaMethod = metaObject->method(index);
        QVariant returnValue;
        QGenericReturnArgument genericResult(metaMethod.typeName(), returnValue.data());
        ArgumentList genericArguments = qVariantListToGenericArguments(argumentList, metaMethod.parameterTypes());

        if (metaMethod.invoke(this,
                              Qt::DirectConnection,
                              genericResult,
                              genericArguments.at(0),
                              genericArguments.at(1),
                              genericArguments.at(2),
                              genericArguments.at(3),
                              genericArguments.at(4),
                              genericArguments.at(5),
                              genericArguments.at(6),
                              genericArguments.at(7),
                              genericArguments.at(8),
                              genericArguments.at(9))) {

            return returnValue;
        }
    }

    return QVariant();
}

bool MetaBridge::is(const QString & ability)
{
    return metaAbilities().contains(ability);
}

QStringList MetaBridge::metaProperties()
{
    if (!m_cache.contains(QLatin1String("metaProperties"))) {
        QStringList * metaProperties = new QStringList();

        const QMetaObject * metaObject = this->metaObject();
        for (int i = 0; i < metaObject->propertyCount(); i++) {
            QByteArray propertyUtf8(metaObject->property(i).name());
            metaProperties->append(QString::fromUtf8(propertyUtf8));
        }

        m_cache.insert(QString("metaProperties"), metaProperties);
    }

    return *(m_cache.object(QLatin1String("metaProperties")));
}

QStringList MetaBridge::metaTasks()
{
    if (!m_cache.contains(QLatin1String("metaTasks"))) {
        QStringList * metaTasks = new QStringList();

        const QMetaObject * metaObject = this->metaObject();
        for (int i = 0; i < metaObject->methodCount(); i++) {
            QByteArray methodeUtf8(metaObject->method(i).signature());
            metaTasks->append(QString::fromUtf8(methodeUtf8));
        }

        m_cache.insert(QLatin1String("metaTasks"), metaTasks);
    }

    return *(m_cache.object(QLatin1String("metaTasks")));
}

QStringList MetaBridge::metaAbilities()
{

    if (!m_cache.contains(QLatin1String("metaAbilities"))) {
        QStringList * metaAbilities = new QStringList();

        const QMetaObject * metaObject = this->metaObject();
        while (metaObject != 0) {
            QByteArray classNameUtf8(metaObject->className());
            metaAbilities->append(QString::fromUtf8(classNameUtf8));
            metaObject = metaObject->superClass();
        }

        m_cache.insert(QLatin1String("metaAbilities"), metaAbilities);
    }

    return *(m_cache.object(QLatin1String("metaAbilities")));
}
