TEMPLATE = lib

TARGET = PluginSystem

include(../puppetlibrary.pri)

INCLUDEPATH += $$PLUGIN_SRC_TREE

HEADERS += $$PWD/pluginmanager.h
HEADERS += $$PWD/plugin.h

SOURCES += $$PWD/pluginmanager.cpp
SOURCES += $$PWD/plugin.cpp
