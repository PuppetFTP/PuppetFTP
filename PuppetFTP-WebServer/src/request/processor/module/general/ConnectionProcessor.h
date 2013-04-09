/*
 * ConnectionProcessor.h
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#ifndef CONNECTIONPROCESSOR_H_
#define CONNECTIONPROCESSOR_H_

#include "AbstractRequestProcessor.h"

class ConnectionProcessor: public AbstractRequestProcessor {
public:
    ConnectionProcessor();
	virtual ~ConnectionProcessor();

	void       process(HTTPRequest& request);
	QByteArray render() const;
};

#endif /* CONNECTIONPROCESSOR_H_ */
