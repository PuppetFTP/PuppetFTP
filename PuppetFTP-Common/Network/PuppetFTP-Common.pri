
QT          += core
QT          -= gui

CONFIG      += console
CONFIG      += debug

TEMPLATE     = app


DEFINES     += __x86__
DEFINES     += __linux__
DEFINES     += __OSVERSION__=2

DEPENDPATH += $$PWD

INCLUDEPATH += /usr/local/include
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/CORBAImpl
INCLUDEPATH += $$PWD/src/CORBAImpl/interface
INCLUDEPATH += $$PWD/src/exception

SOURCES     += src/CommunicationService.cpp
SOURCES     += src/CORBAImpl/Provider.cpp
SOURCES     += src/CORBAImpl/ServiceAdapter.cpp
SOURCES     += src/CORBAImpl/ServiceClientAdapter.cpp
SOURCES     += src/CORBAImpl/typeconverter.cpp
SOURCES     += src/CORBAImpl/interface/ServerConfigHandlerSK.cc
SOURCES     += src/exception/CommunicationException.cpp

HEADERS     += src/INetworkAccessProvider.h
HEADERS     += src/IServerConfigurationProvider.h
HEADERS     += src/CommunicationService.h
HEADERS     += src/CORBAImpl/Provider.h
HEADERS     += src/CORBAImpl/ServiceAdapter.h
HEADERS     += src/CORBAImpl/ServiceClientAdapter.h
HEADERS     += src/CORBAImpl/typeconverter.h
HEADERS     += src/CORBAImpl/interface/ServerConfigHandler.hh
HEADERS     += src/exception/CommunicationException.h

LIBS        += -L /usr/local/lib
LIBS        += -lomnithread
LIBS        += -lomniORB4
LIBS        += -lomniDynamic4
LIBS        += -lomniCodeSets4
LIBS        += -lCOS4
LIBS        += -lCOSDynamic4

QMAKE_RPATHDIR += /usr/local/lib

