#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QString>
#include <QSettings>

class Translate {
public:
    static QString DEFAULT_LOCALE;
private:
    static Translate*   _instance;
    QSettings*          _data;

    Translate();
    virtual ~Translate();

public:
    static Translate*   instance();
    static void         destroy();

    void    group(const QString &grp);
    void    end();
    void    load(const QString &locale = DEFAULT_LOCALE);
    QString tr(const QString &key, const QString& replace = "");
};

#endif // TRANSLATE_H
