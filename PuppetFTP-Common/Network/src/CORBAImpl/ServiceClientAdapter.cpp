/*
 * ServiceClientAdapter.cpp
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#include <QDebug>
#include "ServerConfigHandler.hh"
#include "ServiceClientAdapter.h"
#include "typeconverter.h"

#define ACCESS_ERROR_MESSAGE "Unable to perform operation, please verify your configuration"

namespace CORBA {
namespace Impl {

ServiceClientAdapter::ServiceClientAdapter(const ServerConfigHandler_var& handler) : _handler(handler) {
}

ServiceClientAdapter::~ServiceClientAdapter() {
}


bool ServiceClientAdapter::loadPlugin(const QString & pluginId, const QString & pluginName) {
	try {
		return _handler->loadPlugin(pluginId.toLatin1().data(), pluginName.toLatin1().data());
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return false;
}

bool ServiceClientAdapter::unloadPlugin(const QString & pluginId) {
	try {
		return _handler->unloadPlugin(pluginId.toLatin1().data());
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return false;
}

bool ServiceClientAdapter::set(const QString & pluginId, const QString & propertyName, const QVariant & value) {
	try {
		QScopedPointer<ServerConfigHandler::ByteSequence> valueBytes(::CORBA::converter::fromVariantToByteSequence(value));
		bool r = _handler->set(
				pluginId.toLatin1().data(),
				propertyName.toLatin1().data(),
				*valueBytes.data()
		);
		return r;
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return false;
}

QVariant ServiceClientAdapter::get(const QString & pluginId, const QString & propertyName) {
	try {
		QScopedPointer<ServerConfigHandler::ByteSequence> propBytes(_handler->get(pluginId.toLatin1().data(), propertyName.toLatin1().data()));
		return ::CORBA::converter::fromByteSequenceToVariant(*propBytes);
		} catch (...) {
			qCritical() << ACCESS_ERROR_MESSAGE;
		}
	return QVariant();
}

QVariant ServiceClientAdapter::exec(const QString & pluginId, const QString & taskName, const QVariantList & argumentList) {
	try {
		QScopedPointer<ServerConfigHandler::ByteSequence> argsBytes(::CORBA::converter::fromVariantToByteSequence(QVariant(argumentList)));
		QScopedPointer<ServerConfigHandler::ByteSequence> taskBytes(_handler->exec(
				pluginId.toLatin1().data(),
				taskName.toLatin1().data(),
				*argsBytes.data()
		));
		return ::CORBA::converter::fromByteSequenceToVariant(*taskBytes.data());
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return QVariant();
}

QStringList ServiceClientAdapter::metaProperties(const QString & pluginId) {
	try {
		QScopedPointer<ServerConfigHandler::StringSequence> metaPropSeq(_handler->metaProperties(pluginId.toLatin1().data()));
		QStringList metaPropList = ::CORBA::converter::fromStringSequenceToStringList(*metaPropSeq.data());
		return metaPropList;
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return QStringList();
}

QStringList ServiceClientAdapter::metaTasks(const QString & pluginId) {
	try {
		QScopedPointer<ServerConfigHandler::StringSequence> metaTaskSeq(_handler->metaProperties(pluginId.toLatin1().data()));
		QStringList metaTaskList = ::CORBA::converter::fromStringSequenceToStringList(*metaTaskSeq.data());
		return metaTaskList;
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return QStringList();
}

QString ServiceClientAdapter::lastErrorString() {
	try {
		return QString(_handler->lastErrorString());
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return "";
}

bool ServiceClientAdapter::hasFailure() {
	try {
		return _handler->hasFailure();
	} catch (...) {
		qCritical() << ACCESS_ERROR_MESSAGE;
	}
	return false;
}

} // namespace Impl
} // namespace CORBA
