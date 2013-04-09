include(../../daemon.pri)

TEMPLATE = lib
DESTDIR = $$DAEMON_PLUGIN_PATH
QT += core
CONFIG += qt plugin


INCLUDEPATH += $$PWD
INCLUDEPATH += $$LIBRARY_SRC_TREE/abstractplugin
INCLUDEPATH += $$LIBRARY_SRC_TREE/serverconfig
INCLUDEPATH += $$PLUGIN_SRC_TREE
INCLUDEPATH += $$NETWORK_SRC_TREE
INCLUDEPATH += $$NETWORK_SRC_TREE/CORBAImpl/interface
INCLUDEPATH += $$NETWORK_SRC_TREE/exception

HEADERS += $$PWD/abstractauthentication.h
HEADERS += $$PWD/chrootlist.h
HEADERS += $$PWD/ipluginprovider.h
HEADERS += $$PWD/pamauthentication.h
HEADERS += $$PWD/servicemanager.h

SOURCES += $$PWD/abstractauthentication.cpp
SOURCES += $$PWD/chrootlist.cpp
SOURCES += $$PWD/pamauthentication.cpp
SOURCES += $$PWD/servicemanager.cpp

LIBS += -lAbstractplugin
LIBS += -lCommunication
LIBS += -lServerconfig
