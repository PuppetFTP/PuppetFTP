/*
 * ServiceAdapter.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include "ServiceAdapter.h"
#include "typeconverter.h"

namespace CORBA {
namespace Impl {

ServiceAdapter::ServiceAdapter() : _configurator(0) {
}

ServiceAdapter::ServiceAdapter(IServerConfigurationProvider* provider) : _configurator(provider) {
}

ServiceAdapter::~ServiceAdapter() {
    delete _configurator;
}

::CORBA::Boolean ServiceAdapter::loadPlugin(const char* pluginId, const char* pluginName) {
	return _configurator->loadPlugin(QString(pluginId), QString(pluginName));
}

::CORBA::Boolean ServiceAdapter::unloadPlugin(const char* pluginId) {
	return _configurator->unloadPlugin(QString(pluginId));
}

::CORBA::Boolean ServiceAdapter::set(const char* pluginId, const char* propertyName, const ::ServerConfigHandler::ByteSequence& value) {
	return _configurator->set(
				QString(pluginId),
				QString(propertyName),
				::CORBA::converter::fromByteSequenceToVariant(value)
	);
}

ServerConfigHandler::ByteSequence* ServiceAdapter::get(const char* pluginId, const char* propertyName) {
	return ::CORBA::converter::fromVariantToByteSequence(
				_configurator->get(QString(pluginId), QString(propertyName))
	);
}

ServerConfigHandler::ByteSequence* ServiceAdapter::exec(const char* pluginId, const char* taskName, const ::ServerConfigHandler::ByteSequence& argumentList) {
	return ::CORBA::converter::fromVariantToByteSequence(
				_configurator->exec(
						QString(pluginId),
						QString(taskName),
						::CORBA::converter::fromByteSequenceToVariant(argumentList).toList()
				)
	);
}

ServerConfigHandler::StringSequence* ServiceAdapter::metaProperties(const char* pluginId) {
	return ::CORBA::converter::fromStringListToStringSequence(
				_configurator->metaProperties(QString(pluginId))
	);
}

ServerConfigHandler::StringSequence* ServiceAdapter::metaTasks(const char* pluginId) {
	return ::CORBA::converter::fromStringListToStringSequence(
			_configurator->metaTasks(QString(pluginId))
	);
}

char* ServiceAdapter::lastErrorString() {
	return strdup(_configurator->lastErrorString().toLatin1().data());
}

::CORBA::Boolean ServiceAdapter::hasFailure() {
	return _configurator->hasFailure();
}

} // Impl
} // CORBA

