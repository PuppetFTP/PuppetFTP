#include <stdio.h>
#include <QFile>
#include "Translate.h"
#include <QDebug>
Translate*  Translate::_instance        = 0;
QString     Translate::DEFAULT_LOCALE   = "en_GB";

Translate::Translate() {
}

Translate::~Translate() {
}

Translate* Translate::instance() {
    if (_instance == 0) {
        _instance = new Translate();
        _instance->load();
    }
    return _instance;
}

void Translate::destroy() {
    if (_instance != 0) {
        delete _instance;
        _instance = 0;
    }
}

void Translate::load(const QString& locale) {
    QString path("web/locales/");
    QFile file(path + locale + ".ini");
    path.append((file.exists() ? locale : DEFAULT_LOCALE) + ".ini");
    _data = new QSettings(path, QSettings::IniFormat);
}

void Translate::group(const QString &grp) {
    end();
    _data->beginGroup(grp);
}

void Translate::end() {
    if (!_data->group().isEmpty()) {
        _data->endGroup();
    }
}

QString Translate::tr(const QString &key, const QString& replace) {
    if (!replace.isEmpty())
        return _data->value(key, key).toString().arg(replace);
    return _data->value(key, key).toString();
}

