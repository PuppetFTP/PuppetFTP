#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QString>

#ifdef Q_WS_WIN
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

#define EXPORT_PLUGIN(Clazz)    \
extern "C" EXPORT Clazz * instance() { \
    return new Clazz();         \
}

class Plugin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name() WRITE setName())
    Q_PROPERTY(QString type READ type() WRITE setType())
    Q_PROPERTY(QString path READ path() WRITE setPath())
public:
    Plugin();

    QString name();
    QString type();
    QString path();

    void setName(const QString & name);
    void setType(const QString & type);
    void setPath(const QString & path);

private:
    QString m_name;
    QString m_path;
    QString m_type;
};

#endif // PLUGIN_H
