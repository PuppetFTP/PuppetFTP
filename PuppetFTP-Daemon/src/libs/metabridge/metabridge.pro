TEMPLATE = lib

TARGET = MetaBridge

include(../puppetlibrary.pri)

INCLUDEPATH += $$NETWORK_SRC_TREE
INCLUDEPATH += $$PLUGIN_SRC_TREE

HEADERS += metabridge.h

SOURCES += metabridge.cpp
