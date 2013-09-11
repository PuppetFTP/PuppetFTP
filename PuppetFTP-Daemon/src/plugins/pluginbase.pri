include(../../daemon.pri)

TEMPLATE = lib
DESTDIR = $$DAEMON_PLUGIN_PATH
QT += core
CONFIG += qt plugin

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PLUGIN_SRC_TREE
INCLUDEPATH += $$LIBRARY_SRC_TREE/utils
INCLUDEPATH += $$LIBRARY_SRC_TREE/pluginsystem
INCLUDEPATH += $$LIBRARY_SRC_TREE/metabridge
INCLUDEPATH += $$NETWORK_SRC_TREE
INCLUDEPATH += $$NETWORK_SRC_TREE/exception
INCLUDEPATH += $$NETWORK_SRC_TREE/CORBAImpl/interface

HEADERS += $$PWD/abstractauthentication.h
HEADERS += $$PWD/chrootlist.h
HEADERS += $$PWD/ipluginprovider.h
HEADERS += $$PWD/pamauthentication.h
HEADERS += $$PWD/servicemanager.h

SOURCES += $$PWD/abstractauthentication.cpp
SOURCES += $$PWD/chrootlist.cpp
SOURCES += $$PWD/pamauthentication.cpp
SOURCES += $$PWD/servicemanager.cpp

LIBS += -lPluginSystem
LIBS += -lMetaBridge
LIBS += -lCommunication
LIBS += -lUtils
