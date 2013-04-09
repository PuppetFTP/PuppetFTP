/*
 * HTTPServer.h
 *
 *  Created on: 1 oct. 2012
 *      Author: laplace
 */

#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>

class HTTPServer : public QTcpServer {
	Q_OBJECT
private:
	static QHostAddress DEFAULT_HOSTADDR;
	static quint16      DEFAULT_HOSTPORT;

	QHostAddress _addr;
	quint16      _port;

public:
	HTTPServer(QObject* parent = 0);
	virtual ~HTTPServer();

	void configure();
	void start();
	void incomingConnection(int socket);

private slots:
     void readClient();
     void discardClient();
};

#endif /* HTTPSERVER_H_ */
