include(../../daemon.pri)

DESTDIR = $$DAEMON_LIBRARY_PATH

QT += core
QT -= gui

DEFINES += CORE_LIBRARY

CONFIG += shared dll
