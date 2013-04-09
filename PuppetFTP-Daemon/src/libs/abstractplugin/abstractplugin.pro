TEMPLATE = lib

TARGET = Abstractplugin

include(../puppetlibrary.pri)

INCLUDEPATH += $$LIBRARY_SRC_TREE/serverconfig
INCLUDEPATH += $$NETWORK_SRC_TREE
INCLUDEPATH += $$PLUGIN_SRC_TREE

HEADERS += $$PWD/abstractplugin.h
HEADERS += $$PWD/abstractpluginexception.h
HEADERS += $$PWD/iabstractplugin.h

SOURCES += $$PWD/abstractplugin.cpp
SOURCES += $$PWD/abstractpluginexception.cpp
