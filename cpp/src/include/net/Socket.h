//
// Created by jyates on 4/27/19.
//

#ifndef OPENENGINE_SOCKET_H
#define OPENENGINE_SOCKET_H

#include <memory>

extern "C" {
#include <unistd.h>
};

#include "serialization/Serializable.h"
#include "serialization/Deserializable.h"

namespace OE {

class Socket {
protected:
    explicit Socket(int socketDescriptor);

    const int socketDescriptor;

public:
    virtual ~Socket() = default;

    virtual ssize_t send(std::unique_ptr<Serializable> serializable) = 0;

    virtual ssize_t recv(std::unique_ptr<Deserializable> deserializable) = 0;

};

Socket::Socket(int socketDescriptor) :
        socketDescriptor(socketDescriptor) {
}

}
#endif //OPENENGINE_SOCKET_H
