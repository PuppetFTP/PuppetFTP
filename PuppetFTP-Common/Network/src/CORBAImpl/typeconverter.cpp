/*
 * typeconverter.cpp
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#include "typeconverter.h"

namespace CORBA {
namespace converter {

ServerConfigHandler::ByteSequence* fromVariantToByteSequence(const QVariant& variant) {
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out << variant;
	ServerConfigHandler::ByteSequence* bs = new ServerConfigHandler::ByteSequence();
	bs->length(bytes.size());
	for (int i = 0; i < bytes.size(); i++) {
		(*bs)[i] = bytes[i];
	}
	return bs;
}

QVariant fromByteSequenceToVariant(const ServerConfigHandler::ByteSequence& bs) {
	QVariant variant;
	QByteArray bytes;
	for (unsigned long int i = 0; i < bs.length(); i++) {
		bytes.append(bs[i]);
	}
	QDataStream in(&bytes, QIODevice::ReadOnly);
	in >> variant;
	return variant;
}

ServerConfigHandler::StringSequence* fromStringListToStringSequence(const QStringList& list) {
	ServerConfigHandler::StringSequence* out = new ServerConfigHandler::StringSequence();
	out->length(list.size());
	int i = 0;
	for (QStringList::const_iterator it = list.begin(); it != list.end(); it++, i++) {
		(*out)[i] = (*it).toStdString().c_str();
	}
	return out;
}

QStringList fromStringSequenceToStringList(const ServerConfigHandler::StringSequence& sequence) {
	QStringList sl;
	for (unsigned long int i = 0; i < sequence.length(); i++) {
		sl << QString(sequence[i]);
	}
	return sl;
}

} // namespace converter
} // namespace CORBA
