TEMPLATE = lib

TARGET = Utils

include(../puppetlibrary.pri)

HEADERS += serverconfig.h \
    lasterror.h
SOURCES += serverconfig.cpp \
    lasterror.cpp
