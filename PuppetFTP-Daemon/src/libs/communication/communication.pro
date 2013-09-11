TEMPLATE = lib

TARGET = Communication

include(../puppetlibrary.pri)

DEFINES     += __x86__
DEFINES     += __linux__
DEFINES     += __OSVERSION__=2

#DEPENDPATH += $$DAEMON_SRC_TREE/../PuppetFTP-Common/Network
SOURCE_PATH = $$DAEMON_SRC_TREE/../PuppetFTP-Common/Network/src

INCLUDEPATH += /usr/local/include

INCLUDEPATH += $$SOURCE_PATH
INCLUDEPATH += $$SOURCE_PATH/CORBAImpl
INCLUDEPATH += $$SOURCE_PATH/CORBAImpl/interface
INCLUDEPATH += $$SOURCE_PATH/exception

HEADERS     += $$SOURCE_PATH/INetworkAccessProvider.h
HEADERS     += $$SOURCE_PATH/IServerConfigurationProvider.h
HEADERS     += $$SOURCE_PATH/CommunicationService.h
HEADERS     += $$SOURCE_PATH/CORBAImpl/Provider.h
HEADERS     += $$SOURCE_PATH/CORBAImpl/ServiceAdapter.h
HEADERS     += $$SOURCE_PATH/CORBAImpl/ServiceClientAdapter.h
HEADERS     += $$SOURCE_PATH/CORBAImpl/TypeConverter.h
HEADERS     += $$SOURCE_PATH/CORBAImpl/interface/ServerConfigHandler.hh
HEADERS     += $$SOURCE_PATH/exception/CommunicationException.h

SOURCES     += $$SOURCE_PATH/CommunicationService.cpp
SOURCES     += $$SOURCE_PATH/CORBAImpl/Provider.cpp
SOURCES     += $$SOURCE_PATH/CORBAImpl/ServiceAdapter.cpp
SOURCES     += $$SOURCE_PATH/CORBAImpl/ServiceClientAdapter.cpp
SOURCES     += $$SOURCE_PATH/CORBAImpl/TypeConverter.cpp
SOURCES     += $$SOURCE_PATH/CORBAImpl/interface/ServerConfigHandlerSK.cc
SOURCES     += $$SOURCE_PATH/exception/CommunicationException.cpp

LIBS        += -L /usr/local/lib
LIBS        += -lomnithread
LIBS        += -lomniORB4
LIBS        += -lomniDynamic4
LIBS        += -lomniCodeSets4
LIBS        += -lCOS4
LIBS        += -lCOSDynamic4

