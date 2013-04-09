include(../../daemon.pri)
include(../../../PuppetFTP-Common/QtService/src/qtservice.pri)

TEMPLATE = app

TARGET = $$DAEMON_SERVICE_TARGET

DESTDIR = $$DAEMON_SERVICE_PATH

QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += $$LIBRARY_SRC_TREE/abstractplugin
INCLUDEPATH += $$LIBRARY_SRC_TREE/serverconfig
INCLUDEPATH += $$PLUGIN_SRC_TREE
INCLUDEPATH += $$NETWORK_SRC_TREE
INCLUDEPATH += $$NETWORK_SRC_TREE/CORBAImpl/interface
INCLUDEPATH += $$NETWORK_SRC_TREE/exception

HEADERS += puppetftpservice.h

SOURCES += main.cpp
SOURCES += puppetftpservice.cpp

LIBS *= -lAbstractplugin
LIBS *= -lCommunication
LIBS *= -lServerconfig
LIBS *= -lomnithread
LIBS *= -lomniORB4

QMAKE_RPATHDIR += /usr/local/lib
QMAKE_RPATHDIR += $$DAEMON_LIBRARY_PATH
