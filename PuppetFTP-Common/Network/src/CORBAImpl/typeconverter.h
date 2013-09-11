/*
 * typeconverter.h
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#ifndef TYPECONVERTER_H_
#define TYPECONVERTER_H_

#include <QVariant>
#include <QByteArray>
#include <QStringList>
#include "ServerConfigHandler.hh"


namespace CORBA {
namespace converter {

ServerConfigHandler::ByteSequence* fromVariantToByteSequence(const QVariant& variant);
QVariant fromByteSequenceToVariant(const ServerConfigHandler::ByteSequence& bs);

ServerConfigHandler::StringSequence* fromStringListToStringSequence(const QStringList& list);
QStringList fromStringSequenceToStringList(const ServerConfigHandler::StringSequence& sequence);

} // namespace converter
} // namespace CORBA

#endif /* TYPECONVERTER_H_ */
