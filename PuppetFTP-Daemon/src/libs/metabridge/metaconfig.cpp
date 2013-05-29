#include "metaconfig.h"

#include <QMetaProperty>

MetaConfig::MetaConfig()
{
}

QVariant MetaConfig::get(const QString & propertyName)
{
    const QMetaObject * metaObject = this->metaObject();
    const char * propertyStr = propertyName.toUtf8().constData();

    int index = metaObject->indexOfProperty(propertyStr);
    if (index != -1) {
        QMetaProperty metaProperty = metaObject->property(index);
        if (metaProperty.isReadable() && metaProperty.userType())
            return metaProperty.read(this);
    }

    return QVariant();
}

bool MetaConfig::set(const QString & propertyName, const QVariant & value)
{
    const QMetaObject * metaObject = this->metaObject();
    const char * propertyStr = propertyName.toUtf8().constData();

    int index = metaObject->indexOfProperty(propertyStr) != -1;
    if (index != -1) {
        QMetaProperty metaProperty = metaObject->property(index);
        if (metaProperty.isWritable() && metaProperty.userType())
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

QVariant MetaConfig::exec(const QString & taskName, const QVariantList & argumentList)
{
    const QMetaObject * metaObject = this->metaObject();
    const char * taskStr = taskName.toUtf8().constData();

    int index = metaObject->indexOfMethod(taskStr) != -1;
    if (index != -1) {
        QMetaMethod metaMethod = metaObject->method(index);

        if (metaMethod.access() == QMetaMethod::Public && metaMethod.methodType() == QMetaMethod::Method) {
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
    }

    return QVariant();
}

QStringList MetaConfig::metaProperties()
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

QStringList MetaConfig::metaTasks()
{
    if (!m_cache.contains(QLatin1String("metaTasks"))) {
        QStringList * metaTasks = new QStringList();

        const QMetaObject * metaObject = this->metaObject();
        for (int i = 0; i < metaObject->methodCount(); i++) {
            QMetaMethod metaMethod = metaObject->method(i);
            if (metaMethod.access() == QMetaMethod::Public && metaMethod.methodType() == QMetaMethod::Method) {
                QByteArray methodeUtf8(metaObject->method(i).signature());
                metaTasks->append(QString::fromUtf8(methodeUtf8));
            }
        }

        m_cache.insert(QLatin1String("metaTasks"), metaTasks);
    }

    return *(m_cache.object(QLatin1String("metaTasks")));
}

