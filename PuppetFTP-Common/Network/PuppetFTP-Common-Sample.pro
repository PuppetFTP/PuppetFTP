
TARGET       = PuppetFTP-Common-Sample

QT          += core
QT          -= gui

CONFIG      += console
CONFIG      += debug

TEMPLATE     = app


DEFINES     += __x86__
DEFINES     += __linux__
DEFINES     += __OSVERSION__=2

DESTDIR      = build
OBJECTS_DIR  = build
MOC_DIR      = build
RCC_DIR      = build
UI_DIR       = build

DEPENDPATH  += .
DEPENDPATH  += src/CORBAImpl
DEPENDPATH  += src/CORBAImpl/interface
DEPENDPATH  += src/exception
DEPENDPATH  += src/test

INCLUDEPATH += /usr/local/include
INCLUDEPATH += .
INCLUDEPATH += src/
INCLUDEPATH += src/CORBAImpl
INCLUDEPATH += src/CORBAImpl/interface
INCLUDEPATH += src/exception
INCLUDEPATH += src/test


SOURCES     += src/CommunicationService.cpp
SOURCES     += src/CORBAImpl/Provider.cpp
SOURCES     += src/CORBAImpl/ServiceAdapter.cpp
SOURCES     += src/CORBAImpl/ServiceClientAdapter.cpp
SOURCES     += src/CORBAImpl/typeconverter.cpp
SOURCES     += src/CORBAImpl/interface/ServerConfigHandlerSK.cc
SOURCES     += src/exception/CommunicationException.cpp
SOURCES     += src/test/TestServerConfigProvider.cpp
SOURCES     += src/test/main.cpp

HEADERS     += src/INetworkAccessProvider.h
HEADERS     += src/IServerConfigurationProvider.h
HEADERS     += src/CommunicationService.h
HEADERS     += src/CORBAImpl/Provider.h
HEADERS     += src/CORBAImpl/ServiceAdapter.h
HEADERS     += src/CORBAImpl/ServiceClientAdapter.h
HEADERS     += src/CORBAImpl/typeconverter.h
HEADERS     += src/CORBAImpl/interface/ServerConfigHandler.hh
HEADERS     += src/exception/CommunicationException.h
HEADERS     += src/test/TestServerConfigProvider.h


LIBS        += -L /usr/local/lib
LIBS        += -lomnithread
LIBS        += -lomniORB4
LIBS        += -lomniDynamic4
LIBS        += -lomniCodeSets4
LIBS        += -lCOS4
LIBS        += -lCOSDynamic4

QMAKE_RPATHDIR += /usr/local/lib

QMAKE_CXXFLAGS_DEBUG += -ggdb