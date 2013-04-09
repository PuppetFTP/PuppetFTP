/*
 * ICommunicationService.h
 *
 *  Created on: 9 nov. 2012
 *      Author: laplace
 */

#ifndef INETWORKACCESSPROVIDER_H_
#define INETWORKACCESSPROVIDER_H_

#include <QString>
#include <QMap>
#include "IServerConfigurationProvider.h"

/********************************************************************************/
/**
 * INetworkAccessProvider:
 *   Defines the minimum requirements that a network access provider must
 *   provide. This object can operate on both side, server or client.
 *
 *   Configuration:
 *     The implementation of this interface must provide a way to configure
 *     the object as a server or as a client. Configure operation will have
 *     to create all necessary things to work. Unconfigure operation will
 *     have to release all things previously created and will have to
 *     unexposed the registered services and delete them.
 *
 *   Service management:
 *     When the network provider is configured as a server, the
 *     implementation of this interface has to exposed the given services
 *     over the network and has to managed there life cycle. For example,
 *     the CORBA implementation must register the given services on the
 *     naming services and keep the instances of the service alive.
 *
 *   Use a service from a client:
 *     When the network provider as a client, the implementation of this
 *     interface must be able to retrieve the services over the network
 *     and has to manage data transfer. The implementation is not
 *     responsible of the client life cycle.
 */
class INetworkAccessProvider {
public:
    typedef struct {
        enum  mode { SERVER, CLIENT };
    } MODE;

    virtual ~INetworkAccessProvider() {}

    /********************************************************************************/
    /** Configuration                                                              **/
    /**
     * Configure the network layer. Mode parameter defines if the current instance has
     * to run as a server or a client. Options is a map of parameters used to configure
     * the network layer.
     */
    virtual void configure(MODE::mode mode, const QMap<QString, QString>& options) = 0;
    /**
     * Unconfigure the network layer.
     */
    virtual void unconfigure() = 0;

    /********************************************************************************/
    /** Server side                                                                **/
    /**
     * Register a service provider on the network layer, allowing a client to used it
     * over the network.
     */
    virtual void registerServiceProvider(const QString& name, IServerConfigurationProvider* provider) = 0;
    /**
     * Unregister the given service provider from the network layer.
     */
    virtual void unregisterServiceProvider(IServerConfigurationProvider* provider) = 0;
    /**
     * Unregister the service provider registered as 'name'.
     */
    virtual void unregisterServiceProvider(const QString& name) = 0;

    /********************************************************************************/
    /** Client side                                                                **/
    /**
     * Return an adapter to the service provider registered as 'name'. If the service
     * provider could not be found, a null pointer is returned.
     */
    virtual IServerConfigurationProvider* getServiceClient(const QString& name) = 0;
};

#endif // INETWORKACCESSPROVIDER
