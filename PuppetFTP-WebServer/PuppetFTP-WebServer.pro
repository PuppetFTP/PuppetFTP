############################################################
# PuppetFTP-WebServer
############################################################


QT       += core
QT       += network
QT       += sql
QT       += xml
QT       -= gui

TARGET    = PuppetFTP-WebServer
CONFIG   += debug
CONFIG   += console

CONFIG(release, debug|release) {
    CONFIG += warn_off
}
else {
    CONFIG += warn_on
}

TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG    = -ggdb



############################################################
# Build directories

DESTDIR           = bin

CONFIG(debug, debug|release) {
	OBJECTS_DIR   = build/debug/
	MOC_DIR       = build/debug/
	RCC_DIR       = build/debug/
	UI_DIR        = build/debug/
}
else {
	OBJECTS_DIR   = build/release/
	MOC_DIR       = build/release/
	RCC_DIR       = build/release/
	UI_DIR        = build/release/
}


############################################################
# Sources

SOURCES     += src/component/renderer/PageRenderer.cpp
SOURCES     += src/component/renderer/DefaultPageRenderer.cpp
SOURCES     += src/component/renderer/OutputRendererFactory.cpp
SOURCES     += src/component/model/ModelWidgetFactory.cpp
SOURCES     += src/component/model/editor/AccessibleServerModelEditor.cpp
SOURCES     += src/component/model/editor/CredentialModelEditor.cpp
SOURCES     += src/component/model/editor/RoleModelEditor.cpp
SOURCES     += src/component/model/editor/ServerModelEditor.cpp
SOURCES     += src/component/model/editor/UserModelEditor.cpp
SOURCES     += src/component/model/list/AccessibleServerModelList.cpp
SOURCES     += src/component/model/list/CredentialModelList.cpp
SOURCES     += src/component/model/list/RoleModelList.cpp
SOURCES     += src/component/model/list/ServerModelList.cpp
SOURCES     += src/component/model/list/UserModelList.cpp
SOURCES     += src/component/model/viewer/AccessibleServerModelViewer.cpp
SOURCES     += src/component/model/viewer/CredentialModelViewer.cpp
SOURCES     += src/component/model/viewer/RoleModelViewer.cpp
SOURCES     += src/component/model/viewer/ServerModelViewer.cpp
SOURCES     += src/component/model/viewer/UserModelViewer.cpp
SOURCES     += src/component/server/ServerConfWrapper.cpp
SOURCES     += src/component/server/ServerConfEditor.cpp
SOURCES     += src/component/server/ServerConfList.cpp
SOURCES     += src/component/widget/form/Form.cpp
SOURCES     += src/component/widget/form/field/AbstractWidgetForm.cpp
SOURCES     += src/component/widget/form/field/Input.cpp
SOURCES     += src/component/widget/form/field/InputChoice.cpp
SOURCES     += src/component/widget/form/field/Textarea.cpp
SOURCES     += src/component/widget/special/Breadcrumb.cpp
SOURCES     += src/component/widget/special/Menu.cpp
SOURCES     += src/component/widget/special/Notify.cpp
SOURCES     += src/component/widget/inlinable/Text.cpp
SOURCES     += src/component/widget/inlinable/Link.cpp
SOURCES     += src/component/widget/inlinable/Image.cpp
SOURCES     += src/component/widget/AbstractWidget.cpp
SOURCES     += src/component/widget/Container.cpp
SOURCES     += src/component/widget/List.cpp
SOURCES     += src/component/widget/Table.cpp
SOURCES     += src/component/widget/Title.cpp
SOURCES     += src/exception/RuntimeException.cpp
SOURCES     += src/log/log.cpp
SOURCES     += src/model/AccessibleServerTable.cpp
SOURCES     += src/model/DatabaseManager.cpp
SOURCES     += src/model/PuppetFTPCredentialTable.cpp
SOURCES     += src/model/PuppetFTPRoleTable.cpp
SOURCES     += src/model/Query.cpp
SOURCES     += src/model/ServerCredentialTable.cpp
SOURCES     += src/model/ServerRoleTable.cpp
SOURCES     += src/model/ServerTable.cpp
SOURCES     += src/model/UserTable.cpp
SOURCES     += src/model/entity/ModelEntityFactory.cpp
SOURCES     += src/model/entity/AccessibleServer.cpp
SOURCES     += src/model/entity/Credential.cpp
SOURCES     += src/model/entity/Role.cpp
SOURCES     += src/model/entity/Server.cpp
SOURCES     += src/model/entity/User.cpp
SOURCES     += src/request/dispatcher/RequestDispatcher.cpp
SOURCES     += src/request/processor/RequestProcessorFactory.cpp
SOURCES     += src/request/processor/AbstractRequestProcessor.cpp
SOURCES     += src/request/processor/module/entity/EntityListProcessor.cpp
SOURCES     += src/request/processor/module/entity/EntityViewProcessor.cpp
SOURCES     += src/request/processor/module/entity/EntityEditProcessor.cpp
SOURCES     += src/request/processor/module/entity/EntityDeleteProcessor.cpp
SOURCES     += src/request/processor/module/server/ServerEditProcessor.cpp
SOURCES     += src/request/processor/module/server/ServerListProcessor.cpp
SOURCES     += src/request/processor/module/server/ServerUserListProcessor.cpp
SOURCES     += src/request/processor/module/server/ServerUserEditProcessor.cpp
SOURCES     += src/request/processor/module/server/ServerServiceProcessor.cpp
SOURCES     += src/request/processor/module/general/ImportExportProcessor.cpp
SOURCES     += src/request/processor/module/general/ConnectionProcessor.cpp
SOURCES     += src/request/processor/module/general/DisconnectProcessor.cpp
SOURCES     += src/request/processor/module/general/IndexProcessor.cpp
SOURCES     += src/request/processor/module/general/UnavailableProcessor.cpp
SOURCES     += src/request/processor/module/resource/ResourceProcessor.cpp
SOURCES     += src/request/HTTPRequest.cpp
SOURCES     += src/response/HTTPResponse.cpp
SOURCES     += src/routing/Route.cpp
SOURCES     += src/routing/Router.cpp
SOURCES     += src/server/HTTPServer.cpp
SOURCES     += src/service/PuppetFTPWebServer.cpp
SOURCES     += src/session/Session.cpp
SOURCES     += src/session/SessionManager.cpp
SOURCES     += src/utils/helper/Routing.cpp
SOURCES     += src/utils/helper/String.cpp
SOURCES     += src/xml/RouteReader.cpp
SOURCES     += src/xml/XMLHandlerAdapter.cpp
SOURCES     += src/xml/exception/ParsingException.cpp
SOURCES     += src/main.cpp


HEADERS     += src/component/renderer/PageRenderer.h
HEADERS     += src/component/renderer/DefaultPageRenderer.h
HEADERS     += src/component/renderer/IOutputRenderer.h
HEADERS     += src/component/renderer/OutputRendererFactory.h
HEADERS     += src/component/model/IModelEntity.h
HEADERS     += src/component/model/list/AccessibleServerModelList.h
HEADERS     += src/component/model/list/CredentialModelList.h
HEADERS     += src/component/model/list/IModelList.h
HEADERS     += src/component/model/list/ModelEntityList.h
HEADERS     += src/component/model/list/RoleModelList.h
HEADERS     += src/component/model/list/ServerModelList.h
HEADERS     += src/component/model/list/UserModelList.h
HEADERS     += src/component/model/editor/AccessibleServerModelEditor.h
HEADERS     += src/component/model/editor/CredentialModelEditor.h
HEADERS     += src/component/model/editor/IModelEditor.h
HEADERS     += src/component/model/editor/ModelEntityEditor.h
HEADERS     += src/component/model/editor/RoleModelEditor.h
HEADERS     += src/component/model/editor/ServerModelEditor.h
HEADERS     += src/component/model/editor/UserModelEditor.h
HEADERS     += src/component/model/viewer/AccessibleServerModelViewer.h
HEADERS     += src/component/model/viewer/CredentialModelViewer.h
HEADERS     += src/component/model/viewer/ModelEntityViewer.h
HEADERS     += src/component/model/viewer/IModelViewer.h
HEADERS     += src/component/model/viewer/RoleModelViewer.h
HEADERS     += src/component/model/viewer/ServerModelViewer.h
HEADERS     += src/component/model/viewer/UserModelViewer.h
HEADERS     += src/component/model/ModelWidgetFactory.h
HEADERS     += src/component/widget/form/field/AbstractWidgetForm.h
HEADERS     += src/component/widget/form/field/Input.h
HEADERS     += src/component/widget/form/field/InputChoice.h
HEADERS     += src/component/widget/form/field/Textarea.h
HEADERS     += src/component/widget/form/Form.h
HEADERS     += src/component/widget/form/IWidgetForm.h
HEADERS     += src/component/widget/special/Breadcrumb.h
HEADERS     += src/component/widget/special/Menu.h
HEADERS     += src/component/widget/special/Notify.h
HEADERS     += src/component/widget/inlinable/IInlinable.h
HEADERS     += src/component/widget/inlinable/Image.h
HEADERS     += src/component/widget/inlinable/Link.h
HEADERS     += src/component/widget/inlinable/Text.h
HEADERS     += src/component/widget/AbstractWidget.h
HEADERS     += src/component/widget/IWidget.h
HEADERS     += src/component/widget/Container.h
HEADERS     += src/component/widget/List.h
HEADERS     += src/component/widget/Table.h
HEADERS     += src/component/widget/Title.h
HEADERS     += src/component/widget/Widget.h
HEADERS     += src/component/server/ServerConfWrapper.h
HEADERS     += src/component/server/ServerConfEditor.h
HEADERS     += src/component/server/ServerConfList.h
HEADERS     += src/exception/RuntimeException.h
HEADERS     += src/log/log.h
HEADERS     += src/model/AccessibleServerTable.h
HEADERS     += src/model/DatabaseManager.h
HEADERS     += src/model/ITable.h
HEADERS     += src/model/PuppetFTPCredentialTable.h
HEADERS     += src/model/PuppetFTPRoleTable.h
HEADERS     += src/model/Query.h
HEADERS     += src/model/ServerCredentialTable.h
HEADERS     += src/model/ServerRoleTable.h
HEADERS     += src/model/ServerTable.h
HEADERS     += src/model/Table.h
HEADERS     += src/model/UserTable.h
HEADERS     += src/model/entity/ModelEntityFactory.h
HEADERS     += src/model/entity/AccessibleServer.h
HEADERS     += src/model/entity/Credential.h
HEADERS     += src/model/entity/Role.h
HEADERS     += src/model/entity/Server.h
HEADERS     += src/model/entity/User.h
HEADERS     += src/request/dispatcher/RequestDispatcher.h
HEADERS     += src/request/processor/Processor.h
HEADERS     += src/request/processor/IRequestProcessor.h
HEADERS     += src/request/processor/AbstractRequestProcessor.h
HEADERS     += src/request/processor/RequestProcessorFactory.h
HEADERS     += src/request/processor/module/entity/EntityListProcessor.h
HEADERS     += src/request/processor/module/entity/EntityViewProcessor.h
HEADERS     += src/request/processor/module/entity/EntityEditProcessor.h
HEADERS     += src/request/processor/module/entity/EntityDeleteProcessor.h
HEADERS     += src/request/processor/module/server/ServerEditProcessor.h
HEADERS     += src/request/processor/module/server/ServerListProcessor.h
HEADERS     += src/request/processor/module/server/ServerUserListProcessor.h
HEADERS     += src/request/processor/module/server/ServerUserEditProcessor.h
HEADERS     += src/request/processor/module/server/ServerServiceProcessor.h
HEADERS     += src/request/processor/module/general/ImportExportProcessor.h
HEADERS     += src/request/processor/module/general/ConnectionProcessor.h
HEADERS     += src/request/processor/module/general/DisconnectProcessor.h
HEADERS     += src/request/processor/module/general/IndexProcessor.h
HEADERS     += src/request/processor/module/general/UnavailableProcessor.h
HEADERS     += src/request/processor/module/resource/ResourceProcessor.h
HEADERS     += src/request/HTTPRequest.h
HEADERS     += src/response/HTTPResponse.h
HEADERS     += src/routing/Route.h
HEADERS     += src/routing/Router.h
HEADERS     += src/server/HTTPServer.h
HEADERS     += src/service/PuppetFTPWebServer.h
HEADERS     += src/session/Session.h
HEADERS     += src/session/SessionManager.h
HEADERS     += src/utils/Factory.h
HEADERS     += src/utils/helper/Helper.h
HEADERS     += src/xml/RouteReader.h
HEADERS     += src/xml/XMLHandlerAdapter.h
HEADERS     += src/xml/exception/ParsingException.h


INCLUDEPATH += src
INCLUDEPATH += src/component
INCLUDEPATH += src/component/model
INCLUDEPATH += src/component/model/editor
INCLUDEPATH += src/component/model/list
INCLUDEPATH += src/component/model/viewer
INCLUDEPATH += src/component/renderer
INCLUDEPATH += src/component/server
INCLUDEPATH += src/component/widget
INCLUDEPATH += src/component/widget/form
INCLUDEPATH += src/component/widget/form/field
INCLUDEPATH += src/component/widget/special
INCLUDEPATH += src/component/widget/inlinable
INCLUDEPATH += src/exception
INCLUDEPATH += src/log
INCLUDEPATH += src/model
INCLUDEPATH += src/model/entity
INCLUDEPATH += src/model/form
INCLUDEPATH += src/request
INCLUDEPATH += src/request/dispatcher
INCLUDEPATH += src/request/dispatcher/exception
INCLUDEPATH += src/request/processor
INCLUDEPATH += src/request/processor/module/entity
INCLUDEPATH += src/request/processor/module/general
INCLUDEPATH += src/request/processor/module/resource
INCLUDEPATH += src/request/processor/module/server
INCLUDEPATH += src/response
INCLUDEPATH += src/routing
INCLUDEPATH += src/server
INCLUDEPATH += src/service
INCLUDEPATH += src/session
INCLUDEPATH += src/utils
INCLUDEPATH += src/utils/helper
INCLUDEPATH += src/xml
INCLUDEPATH += src/xml/exception


DEPENDPATH += src
DEPENDPATH += src/component
DEPENDPATH += src/component/model
DEPENDPATH += src/component/model/editor
DEPENDPATH += src/component/model/list
DEPENDPATH += src/component/model/viewer
DEPENDPATH += src/component/helper
DEPENDPATH += src/component/server
DEPENDPATH += src/component/renderer
DEPENDPATH += src/component/widget
DEPENDPATH += src/component/widget/form
DEPENDPATH += src/component/widget/form/field
DEPENDPATH += src/component/widget/special
DEPENDPATH += src/component/widget/inlinable
DEPENDPATH += src/exception
DEPENDPATH += src/log
DEPENDPATH += src/model
DEPENDPATH += src/model/entity
DEPENDPATH += src/model/form
DEPENDPATH += src/request
DEPENDPATH += src/request/dispatcher
DEPENDPATH += src/request/dispatcher/exception
DEPENDPATH += src/request/processor
DEPENDPATH += src/request/processor/module/entity
DEPENDPATH += src/request/processor/module/general
DEPENDPATH += src/request/processor/module/resource
DEPENDPATH += src/request/processor/module/server
DEPENDPATH += src/response
DEPENDPATH += src/routing
DEPENDPATH += src/server
DEPENDPATH += src/service
DEPENDPATH += src/session
DEPENDPATH += src/utils
DEPENDPATH += src/utils/helper
DEPENDPATH += src/xml
DEPENDPATH += src/xml/exception

include(../PuppetFTP-Common/QtService/src/qtservice.pri)
include(../PuppetFTP-Common/Network/PuppetFTP-Common.pri)
