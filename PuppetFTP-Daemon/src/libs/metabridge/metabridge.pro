TEMPLATE = lib

TARGET = MetaBridge

include(../puppetlibrary.pri)

INCLUDEPATH += $$LIBRARY_SRC_TREE/utils
INCLUDEPATH += $$LIBRARY_SRC_TREE/pluginsystem
INCLUDEPATH += $$NETWORK_SRC_TREE

HEADERS += $$PWD/metaconfig.h
HEADERS += $$PWD/metaplugin.h
HEADERS += $$PWD/metaconfigdriver.h

SOURCES += $$PWD/metaconfig.cpp
SOURCES += $$PWD/metaplugin.cpp
SOURCES += $$PWD/metaconfigdriver.cpp

LIBS += -lCommunication
LIBS += -lUtils
LIBS += -lPluginSystem
