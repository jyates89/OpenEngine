//
// Created by jyates on 6/1/19.
//

extern "C" {
#include <sys/types.h>
#include <netdb.h>
};

#include "net/Socket.h"
#include "net/builders/HintBuilder.h"
#include "net/TCPServer.h"

namespace OE {

TCPServer::TCPServer(std::string port) {
    struct addrinfo hints = Socket::hintBuilder()
            .asServer()
            .withTCP()
            .build();


    struct addrinfo* results = nullptr;
    int result = getaddrinfo(nullptr, port.c_str(),
            &hints, &results);
    if (result) {
        throw std::runtime_error("failed to ");
    }

    int fd = socket(results->ai_family,
            results->ai_socktype,
            results->ai_protocol);

    result = bind(fd, results->ai_addr, results->ai_addrlen);
    if (result) {
        throw std::runtime_error("failed to bind to port");
    }

    freeaddrinfo(results);

}

void TCPServer::run() {

}

void TCPServer::terminate() {

}

}
