/*
 * CommunicationService.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef COMMUNICATIONSERVICE_H_
#define COMMUNICATIONSERVICE_H_

#include <QMutex>
#include "INetworkAccessProvider.h"

/********************************************************************************/
/**
 * This class is the access point to the communication layer. This class allow the
 * user to register a INetworkAccessProvider which has to deal with communication
 * operations. This class allow the user to register a service without any knowledge
 * on the network implementation. It allows also to use a service over the network
 * without any knowledge. The user just has to register an object implementing the
 * IServiceConfigurationProvider interface and then to retrieve an instance of a
 * previously registered service.
 */
class CommunicationService {
private:
    static CommunicationService* _instance;
    static QMutex                _lock;
    INetworkAccessProvider*      _provider;

    CommunicationService();
    CommunicationService(const CommunicationService&);
    CommunicationService& operator=(const CommunicationService&);
    virtual ~CommunicationService();

    static void instance();

public:
    /** Define the network access provider. **/
    static void                    setProvider(INetworkAccessProvider* provider);
    /** Configure the network layer. **/
    static void                    configure(INetworkAccessProvider::MODE::mode mode, const QMap<QString, QString>& options);
    /** Return the current network access provider. **/
    static INetworkAccessProvider* provider();
    /** Release all resources. **/
    static void                    dispose();
};

#endif /* COMMUNICATIONSERVICE_H_ */
