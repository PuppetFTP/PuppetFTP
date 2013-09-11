include(../../daemon.pri)
include(../../../PuppetFTP-Common/QtService/src/qtservice.pri)

TEMPLATE = app

TARGET = $$DAEMON_SERVICE_TARGET

DESTDIR = $$DAEMON_SERVICE_PATH

QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += $$LIBRARY_SRC_TREE/utils
INCLUDEPATH += $$LIBRARY_SRC_TREE/pluginsystem
INCLUDEPATH += $$LIBRARY_SRC_TREE/metabridge
INCLUDEPATH += $$PLUGIN_SRC_TREE
INCLUDEPATH += $$NETWORK_SRC_TREE
INCLUDEPATH += $$NETWORK_SRC_TREE/CORBAImpl/interface
INCLUDEPATH += $$NETWORK_SRC_TREE/exception

HEADERS += puppetftpservice.h

SOURCES += main.cpp
SOURCES += puppetftpservice.cpp

LIBS *= -lCommunication
LIBS *= -lUtils
LIBS *= -lPluginSystem
LIBS *= -lMetaBridge
LIBS *= -lServerconfig
LIBS *= -lomnithread
LIBS *= -lomniORB4

QMAKE_RPATHDIR += /usr/local/lib
QMAKE_RPATHDIR += $$DAEMON_LIBRARY_PATH
