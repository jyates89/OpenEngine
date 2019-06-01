//
// Created by jyates on 4/27/19.
//

#ifndef OPENENGINE_TCPSOCKET_H
#define OPENENGINE_TCPSOCKET_H

#include "Socket.h"

namespace OE {

class TCPSocket : public Socket {
public:
    explicit TCPSocket(int socketDescriptor);

    virtual ~TCPSocket();

    ssize_t send(std::unique_ptr<Serializable> serializable) override;

    ssize_t recv(std::unique_ptr<Deserializable> deserializable) override;
};

TCPSocket::TCPSocket(int socketDescriptor) :
        Socket(socketDescriptor) {

}

TCPSocket::~TCPSocket() {

}

ssize_t TCPSocket::send(std::unique_ptr<Serializable> serializable) {
    return 0;
}

ssize_t TCPSocket::recv(std::unique_ptr<Deserializable> deserializable) {
    return 0;
}

}

#endif //OPENENGINE_TCPSOCKET_H
