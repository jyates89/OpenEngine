//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_TCPCLIENT_H
#define OPENENGINE_TCPCLIENT_H

#include "StandardDefines.h"
#include "TCPSocket.h"

#include <string>
#include <memory>

namespace OE {

class TCPClient {
public:
    class TCPClientBuilder {
        friend TCPClient;

        std::string hostname;
        std::string port;

    public:
        TCPClient build() {
            return TCPClient(*this);
        }

        TCPClientBuilder withHostname(std::string hostname);

        TCPClientBuilder withPort(std::string port);
    };

    static TCPClientBuilder builder();

private:
    explicit TCPClient(TCPClientBuilder builder);

    std::string hostname;
    std::string port;
};

TCPClient::TCPClientBuilder TCPClient::TCPClientBuilder::withHostname(std::string hostname) {
    this->hostname = std::move(hostname);
    return *this;
}

TCPClient::TCPClientBuilder TCPClient::TCPClientBuilder::withPort(std::string port) {
    this->port = std::move(port);
    return *this;
}

TCPClient::TCPClient(TCPClient::TCPClientBuilder builder) {
    hostname = builder.hostname;
    port     = builder.port;
}

TCPClient::TCPClientBuilder TCPClient::builder() {
    return { };
}

}

#endif //OPENENGINE_TCPCLIENT_H
