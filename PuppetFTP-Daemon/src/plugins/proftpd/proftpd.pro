include(../pluginbase.pri)

TARGET = proftpd

INCLUDEPATH += $$LIBRARY_SRC_TREE/pluginsystem
INCLUDEPATH += $$LIBRARY_SRC_TREE/metabridge

SOURCES += proftpd.cpp
SOURCES += proftpdconfig.cpp
SOURCES += proftpdparser.cpp

HEADERS += proftpd.h
HEADERS += proftpdconfig.h
HEADERS += proftpdparser.h

