/*
 * Provider.cpp
 *
 *  Created on: 27 mars 2012
 *      Author: Cedric Laplace
 */

#include <QDebug>
#include "Provider.h"
#include "CommunicationException.h"
#include "ServiceClientAdapter.h"

namespace CORBA {
namespace Impl {

Provider::Provider() : _orb(0), _poa(0), _naming(0) {
}

Provider::~Provider() {
    for (QMap<QString, ServiceAdapter*>::iterator it = _handlers.begin(); it != _handlers.end(); it++) {
        delete *it;
    }
}


void Provider::configure(MODE::mode mode, const QMap<QString, QString>& options) {
    qDebug() << "Configuring CORBA Provider...";
    // Provider...
    try {
        char* args[] = { 0 };
        int argc     = 0;

//        const char* opts[options.size() + 1][2];
//        opts[options.size()][0] = 0;
//        opts[options.size()][1] = 0;
//        int i = 0;
//        for (QMap<QString, QString>::const_iterator it = options.begin(); it != options.end(); i++, it++) {
//            opts[i][0] = strdup(it.key().toStdString().c_str());
//            opts[i][1] = strdup(it.value().toStdString().c_str());
//        }
        const char* opts[2][2];
        if (options.contains("InitRef")) {
            opts[0][0] = strdup("InitRef");
            opts[0][1] = strdup(options["InitRef"].toStdString().c_str());
        }
        else {
            opts[0][0] = 0;
            opts[0][1] = 0;
        }
        opts[1][0] = 0;
        opts[1][1] = 0;

        this->_orb = CORBA::ORB_init(argc, args, "omniORB4", opts);
        if (mode == INetworkAccessProvider::MODE::SERVER) {
            this->_poa = PortableServer::POA::_narrow(this->_orb->resolve_initial_references("RootPOA"));
            if (CORBA::is_nil(this->_poa)) {
                throw CommunicationException("Failed to narrow the root POA.");
            }
        }

        this->_naming = CosNaming::NamingContext::_narrow(this->_orb->resolve_initial_references("NameService"));
        if (CORBA::is_nil(this->_naming)) {
            throw CommunicationException("Failed to narrow the root naming context.");
        }

        if (mode == INetworkAccessProvider::MODE::SERVER) {
            CosNaming::Name contextName;
            contextName.length(1);
            contextName[0].id = CONTEXT_NAME_ID;
            contextName[0].kind = CONTEXT_NAME_KIND;
            try {
                this->_naming->bind_new_context(contextName);
            } catch(CosNaming::NamingContext::AlreadyBound& ex) {
                //std::cerr << "Server context already exists, trying to narrow existing context." << std::endl;
                if (CORBA::is_nil(CosNaming::NamingContext::_narrow(this->_naming->resolve(contextName)))) {
                    throw CommunicationException("Failed to narrow naming context.");
                }
            }
        }
    // For details on CORBA Exception:
    //   http://techpubs.borland.com/am/bes/v6/en/updates/except_cpp.html
    } catch (const CORBA::NO_RESOURCES& e) {
        throw CommunicationException("No resources found, please verify the configuration of omniORB.");
    } catch (const CORBA::ORB::InvalidName& e) {
        throw CommunicationException("Service required is invalid or does not exist.");
    } catch(const CORBA::TRANSIENT& e) {
        throw CommunicationException("The naming service could not be found, make sure it is correctly started.");
    } catch(CORBA::SystemException & e) {
        throw CommunicationException(QString("Receive a CORBA system error: ") + e._name());
    } catch(const CORBA::Exception& e) {
        std::string err();
        throw CommunicationException(QString("Receive a CORBA error: ") + e._name());
    } catch(const omniORB::fatalException& e) {
        std::string err();
        throw CommunicationException(QString("Receive an omniORB fatal error: ") + e.errmsg());
    } catch (const CommunicationException& e) {
        throw e;
    } catch (...) {
        throw CommunicationException("An unknown error occurred while configuring the network layer.");
    }
    qDebug() << "Configuration of CORBA Provider done, ready.";
}

void Provider::unconfigure() {
    if (this->_orb)
        this->_orb->destroy();
}

void Provider::registerServiceProvider(const QString& name, IServerConfigurationProvider* provider) {
    if (CORBA::is_nil(this->_naming)) {
        throw CommunicationException("Naming service is not properly started, cannot register provider");
    }
    try {
        ServiceAdapter* handler = new ServiceAdapter(provider);
        _handlers[name] = handler;
        this->_poa->activate_object(handler);
        this->bindObjectToName(name.toStdString().c_str(), handler->_this());
        handler->_remove_ref();
        this->_poa->the_POAManager()->activate();
    } catch(const CORBA::SystemException& e) {
        throw CommunicationException(QString("Receive a corba system error: ") + e._name());
    } catch(const CORBA::Exception& e) {
        throw CommunicationException(QString("Receive a corba error: ") + e._name());
    } catch(const omniORB::fatalException& e) {
        throw CommunicationException(QString("Receive an omniORB fatal error: ") + e.errmsg());
    }
}

void Provider::unregisterServiceProvider(const QString& name) {
    _handlers.remove(name);
}

IServerConfigurationProvider* Provider::getServiceClient(const QString& name) {
    if (CORBA::is_nil(this->_naming)) {
        throw CommunicationException("Naming service is not properly started, cannot locate provider");
    }
    try {
        CosNaming::Name cname;
        cname.length(2);
        cname[0].id   = CONTEXT_NAME_ID;
        cname[0].kind = CONTEXT_NAME_KIND;
        cname[1].id   = name.toStdString().c_str();
        cname[1].kind = CONTEXT_OBJECT_KIND;
        return new ServiceClientAdapter(ServerConfigHandler::_narrow(this->_naming->resolve(cname)));
    } catch (const CORBA::COMM_FAILURE& e) {
        throw CommunicationException("Cannot communicate with the naming service, make sure it is still alive.");
    } catch (...) {
        throw CommunicationException("An unknown error occurred, unable to retrieve the requested service.");
    }
    return 0;
}

void Provider::run() {
    this->_orb->run();
}

void Provider::bindObjectToName(const char* name, CORBA::Object_ptr objectRef) {
    try {
        CosNaming::Name objectName;
        objectName.length(2);
        objectName[0].id = CONTEXT_NAME_ID;
        objectName[0].kind = CONTEXT_NAME_KIND;
        objectName[1].id = name;
        objectName[1].kind = CONTEXT_OBJECT_KIND;
        try {
            this->_naming->bind(objectName, objectRef);
        } catch(CosNaming::NamingContext::AlreadyBound& ex) {
            this->_naming->rebind(objectName, objectRef);
        }
    } catch(CORBA::TRANSIENT &) {
        throw CommunicationException("The naming service could not be found, make sure it is correctly started.");
    } catch(CORBA::SystemException & e) {
        throw CommunicationException(QString("Receive a corba system error: ") + e._name());
    }
}

} // Impl
} // CORBA
