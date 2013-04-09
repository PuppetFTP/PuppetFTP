/*
 * NetworkForm.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#include "NetworkForm.h"
#include "Select.h"

namespace Widget {
namespace ServerConfig {

NetworkForm::~NetworkForm() {
    QMap<QString, QString> ipOptions;
    ipOptions["IPv4"] = "IPv4";
    ipOptions["IPv6"] = "IPv6";
    ipOptions["Undefined"] = "Undefined";
    addWidget("ip", new Widget::Form::Select("ip", "Internet Protocol", ipOptions, ipOptions["IPv4"]));
    addWidget("idle_timeout", new Widget::Form::InputText("idle_timeout", "Idle timeout", 300));
    addWidget("data_timeout", new Widget::Form::InputText("data_timeout", "Data connection timeout", 300));
}

NetworkForm::NetworkForm() {
}

void NetworkForm::bind(IServerConfigurationProvider* server) {
    if (server->getInternetProtocol() == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv4)
        getWidget("ip")->setValue("IPv4");
    else if (server->getInternetProtocol() == IServerConfigurationProvider::INTERNET_PROTOCOL::IPv6)
        getWidget("ip")->setValue("IPv6");
    else
        getWidget("ip")->setValue("Undefined");
    getWidget("idle_timeout")->setValue(server->getIdleTimeout());
    getWidget("data_timeout")->setValue(server->getDataConnectionTimeout());
}

} // namespace ServerConfig
} // namespace Widget
