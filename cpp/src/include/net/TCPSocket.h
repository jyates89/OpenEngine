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

    ~TCPSocket() override = default;

    ssize_t send(
            std::unique_ptr<Serializable> serializable,
            int flags) override;

    ssize_t recv(
            std::unique_ptr<Deserializable> deserializable,
            int flags) override;
};

}

#endif //OPENENGINE_TCPSOCKET_H
